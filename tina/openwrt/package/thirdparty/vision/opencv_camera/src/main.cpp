#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/fb.h>
#include <signal.h>
#include <stdint.h>
#include <sys/ioctl.h>

#include <opencv2/opencv.hpp>

#define DISPLAY_X 240
#define DISPLAY_Y 240

static cv::VideoCapture cap;

struct framebuffer_info {
    uint32_t bits_per_pixel;
    uint32_t xres_virtual;
};

struct framebuffer_info get_framebuffer_info(const char* framebuffer_device_path)
{
    struct framebuffer_info info;
    struct fb_var_screeninfo screen_info;
    int fd = -1;
    fd = open(framebuffer_device_path, O_RDWR);
    if (fd >= 0) {
        if (!ioctl(fd, FBIOGET_VSCREENINFO, &screen_info)) {
            info.xres_virtual = screen_info.xres_virtual;
            info.bits_per_pixel = screen_info.bits_per_pixel;
        }
    }
    return info;
};

/* Signal handler */
static void terminate(int sig_no)
{
    printf("Got signal %d, exiting ...\n", sig_no);
    cap.release();
    exit(1);
}

static void install_sig_handler(void)
{
    signal(SIGBUS, terminate);
    signal(SIGFPE, terminate);
    signal(SIGHUP, terminate);
    signal(SIGILL, terminate);
    signal(SIGINT, terminate);
    signal(SIGIOT, terminate);
    signal(SIGPIPE, terminate);
    signal(SIGQUIT, terminate);
    signal(SIGSEGV, terminate);
    signal(SIGSYS, terminate);
    signal(SIGTERM, terminate);
    signal(SIGTRAP, terminate);
    signal(SIGUSR1, terminate);
    signal(SIGUSR2, terminate);
}

int main(int, char**)
{
    const int frame_width = 480;
    const int frame_height = 480;
    const int frame_rate = 30;

    install_sig_handler();

    framebuffer_info fb_info = get_framebuffer_info("/dev/fb0");

    cap.open(0);

    if (!cap.isOpened()) {
        std::cerr << "Could not open video device." << std::endl;
        return 1;
    }

    std::cout << "Successfully opened video device." << std::endl;
    cap.set(cv::CAP_PROP_FRAME_WIDTH, frame_width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, frame_height);
    cap.set(cv::CAP_PROP_FPS, frame_rate);

    std::ofstream ofs("/dev/fb0");

    cv::Mat frame;
    cv::Mat trams_temp_fream;
    cv::Mat yuv_frame;

    while (true) {
        cap >> frame;
        if (frame.depth() != CV_8U) {
            std::cerr << "Not 8 bits per pixel and channel." << std::endl;
        } else if (frame.channels() != 3) {
            std::cerr << "Not 3 channels." << std::endl;
        } else {
            cv::transpose(frame, frame);
            cv::flip(frame, frame, 0);
            cv::resize(frame, frame, cv::Size(DISPLAY_X, DISPLAY_Y));
            int framebuffer_width = fb_info.xres_virtual;
            int framebuffer_depth = fb_info.bits_per_pixel;
            cv::Size2f frame_size = frame.size();
            cv::Mat framebuffer_compat;
            switch (framebuffer_depth) {
            case 16:
                cv::cvtColor(frame, framebuffer_compat, cv::COLOR_BGR2BGR565);
                for (int y = 0; y < frame_size.height; y++) {
                    ofs.seekp(y * framebuffer_width * 2);
                    ofs.write(reinterpret_cast<char*>(framebuffer_compat.ptr(y)), frame_size.width * 2);
                }
                break;
            case 32: {
                std::vector<cv::Mat> split_bgr;
                cv::split(frame, split_bgr);
                split_bgr.push_back(cv::Mat(frame_size, CV_8UC1, cv::Scalar(255)));
                cv::merge(split_bgr, framebuffer_compat);
                for (int y = 0; y < frame_size.height; y++) {
                    ofs.seekp(y * framebuffer_width * 4);
                    ofs.write(reinterpret_cast<char*>(framebuffer_compat.ptr(y)), frame_size.width * 4);
                }
            } break;
            default:
                std::cerr << "Unsupported depth of framebuffer." << std::endl;
            }
        }
    }
}
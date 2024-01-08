#pragma once

#define LOG(message, ...) printf("[%s:%d] " message "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define HAS_FAILED(errorCode) errorCode != 10000
enum ErrorCode {
    Success = 10000,
    ServerInitializationError,
    SocketError,
    ThreadError
};

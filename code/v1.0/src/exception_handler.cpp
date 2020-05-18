#include "exception_handler.h"

enum class ExceptionCode { CANNOT_GO_TO_GOAL };

void handle_exception(ExceptionCode exception_code) {
    switch (exception_code) {
    case ExceptionCode::CANNOT_GO_TO_GOAL:
        // TODO
        break;

    default:
        ROS_ERROR("Exception code not supported!");
    }
}
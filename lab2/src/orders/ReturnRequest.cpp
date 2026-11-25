#include "lab2/orders/ReturnRequest.hpp"

ReturnRequest::ReturnRequest(Order order, std::string reason)
    : order_(order), reason_(reason), isApproved_(false) {}
void ReturnRequest::approve() { isApproved_ = true; }
bool ReturnRequest::isApproved() const { return isApproved_; }

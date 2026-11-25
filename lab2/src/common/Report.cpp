#include "lab2/common/Report.hpp"
Report::Report(std::string title) : title_(title) {}
void Report::setContent(std::string content) { content_ = content; }
std::string Report::getTitle() const { return title_; }

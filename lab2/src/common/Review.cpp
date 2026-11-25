#include "lab2/common/Review.hpp"
Review::Review(std::string text, std::string authorName) : text_(text), authorName_(authorName) {}
std::string Review::getText() const { return text_; }

#pragma once

class NonCopyable
{
public:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = default;

    NonCopyable& operator= (const NonCopyable&) = delete;
    NonCopyable& operator= (NonCopyable&& p) = default;
};
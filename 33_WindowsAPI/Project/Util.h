#pragma once

template <typename T>
static T GetRandom(const T& start, const T& end)
{
    if (start >= end)
        return (T)0;

    return start + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (end - start)));
}

template <typename T>
static void Clamp(T& target, const T& floor, const T& ceil)
{
    if (target < floor) target = floor;
    else if (target > ceil) target = ceil;
}

template <typename T>
static T MappingtoNewRange(T num, T in_min, T in_max, T out_min, T out_max)
{
    return (T)(((num - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min);
}

static TCHAR lpOut[1024];
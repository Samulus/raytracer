//
// color.h
// Author: Samuel Vargas
// Date: 08/18/2019
//

#pragma once
#include <linalg.h>
static constexpr auto RED = linalg::vec<float,3>(1, 0, 0);
static constexpr auto GREEN = linalg::vec<float,3>(0, 1, 0);
static constexpr auto BLUE = linalg::vec<float,3>(0, 0, 1);

static constexpr auto CYAN = linalg::vec<float,3>(0, 1, 1);
static constexpr auto YELLOW = linalg::vec<float,3>(1, 1, 0);
static constexpr auto MAGENTA = linalg::vec<float,3>(1, 0, 1);

static constexpr auto PURPLE = linalg::vec<float,3>(0.5, 0, 1);
static constexpr auto PINK = linalg::vec<float,3>(1, 0, 0.5);
static constexpr auto LIME = linalg::vec<float,3>(0.5, 1, 0);


static constexpr auto WHITE = linalg::vec<float,3>(1, 1, 1);
static constexpr auto BLACK = linalg::vec<float,3>(0, 0, 0);
static constexpr auto ORANGE = linalg::vec<float,3>(170.0 / 255.0, 116.0 / 255.0, 57.0 / 255.0);
static constexpr auto GREY = linalg::vec<float,3>(82.0/255.0, 82.0/255.0, 82.0/255.0);

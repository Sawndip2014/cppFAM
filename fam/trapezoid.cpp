//
//  trapezoid.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//
//  This file is part of The C++ Fuzzy Associative Memory
//  http://github.com/cpowell/fuzzy-associative-memory-cplusplus
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the library.
//

#include "trapezoid.h"

fuzzy::Trapezoid::Trapezoid(const double l, const double tl, const double tr, const double r, const double h) :
_left(l),
_top_left(tl),
_top_right(tr),
_right(r)
{
    _height=h;
}

fuzzy::Trapezoid::Trapezoid() :
_left(0),
_top_left(0),
_top_right(0),
_right(0)
{
    _height=0;
}

double fuzzy::Trapezoid::calculateMu(const double value) const {
    if (value < _left || value > _right) {
        return 0.0;
    } else if (value >= _left && value < _top_left) {
        return (value - _left) / (_top_left - _left);
    } else if (value >= _top_left && value <= _top_right) {
        return 1.0;
    } else {
        return (_right - value) / (_right - _top_right);
    }
}

double fuzzy::Trapezoid::calculateXCentroid() const {
    double a = _top_right - _top_left;
    double b = _right - _left;
    double c = _top_left - _left;

    double cx = (2.0*a*c + pow(a,2.0) + c*b + a*b + pow(b,2.0)) / (3.0 * (a+b));
    return cx+_left;
}

std::shared_ptr<fuzzy::FuzzySet> fuzzy::Trapezoid::larsen(const double ratio) const {
    std::shared_ptr<Trapezoid> dup(new Trapezoid(*this));
    dup->setHeight(_height * ratio);
    return dup;
}

std::shared_ptr<fuzzy::FuzzySet> fuzzy::Trapezoid::mamdami(const double clip_height) const {
    double l = _left;
    double tl = _left + (clip_height * (_top_left - _left));
    double tr = _right + (clip_height * (_right - _top_right));
    double r = _right;

    return std::make_shared<Trapezoid>(l, tl, tr, r, clip_height);
}

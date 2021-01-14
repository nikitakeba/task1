#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    int x;
    int y;

    Point(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
};

bool operator<(Point &p1, Point &p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

bool operator>(Point &p1, Point &p2) {
    return (p1.x > p2.x) || (p1.x == p2.x && p1.y > p2.y);
}

bool operator==(Point &p1, Point &p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

std::istream &operator>>(std::istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
}

std::ostream &operator<<(std::ostream &os, Point &p) {
    os << p.x << ' ' << p.y;
    return os;
}

double euclidean_distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

struct Vector {
    int x;
    int y;

    Vector(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
};

//vector P1P2
Vector get_vector(Point p1, Point p2) {
    return Vector(p2.x - p1.x, p2.y - p1.y);
}

struct segment {
    Point p1, p2;

    segment(Point _p1 = Point(), Point _p2 = Point()) {
        p1 = _p1;
        p2 = _p2;
    }

    segment(int x1, int y1, int x2, int y2) {
        p1.x = x1;
        p1.y = y1;
        p2.x = x2;
        p2.y = y2;
    }
};

bool operator<(segment &s1, segment &s2) {
    return s1.p1 < s2.p1 || (s1.p1 == s2.p1 && s1.p2 < s2.p2);
}

bool operator==(segment &s1, segment &s2) {
    return (s1.p1 == s2.p1 && s1.p2 == s2.p2);
}

std::istream &operator>>(std::istream &is, segment &s) {
    is >> s.p1 >> s.p2;
    return is;
}

std::ostream &operator<<(std::ostream &os, segment &s) {
    os << s.p1 << ' ' << s.p2;
    return os;
}

int pseudoscalar_product(Vector &v1, Vector &v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

bool on_the_same_line(Point p1, Point p2, Point p3) {
    Vector v1 = get_vector(p1, p2), v2 = get_vector(p1, p3);
    if (pseudoscalar_product(v1, v2) == 0)
        return true;
    else
        return false;
}

// Checks whether Point p belongs to segment p1p2 (Points p, p1, p2 are collinear)
bool belongs_to_segment(Point p, segment s) {
    return abs((euclidean_distance(p, s.p1) + euclidean_distance(p, s.p2)) - euclidean_distance(s.p1, s.p2)) < 1e-9;
}

bool overlap(segment s1, segment s2) {
    if (!on_the_same_line(s1.p1, s2.p1, s2.p2) || !on_the_same_line(s1.p2, s2.p1, s2.p2))
        return false;
    if (belongs_to_segment(s1.p1, s2) || belongs_to_segment(s1.p1, s2) ||
        belongs_to_segment(s2.p1, s1) || belongs_to_segment(s2.p2, s1)) {
        return true;
    } else {
        return false;
    }
}

segment new_segment(segment s1, segment s2) {
    segment s = segment(Point(INT_MAX, INT_MAX), Point(INT_MIN, INT_MIN));
    if (s1.p1 < s.p1)
        s.p1 = s1.p1;
    if (s1.p2 < s.p2)
        s.p1 = s1.p2;
    if (s2.p1 < s.p1)
        s.p1 = s2.p1;
    if (s2.p2 < s.p2)
        s.p1 = s2.p2;

    if (s1.p1 > s.p1)
        s.p2 = s1.p1;
    if (s1.p2 > s.p2)
        s.p2 = s1.p2;
    if (s2.p1 > s.p1)
        s.p2 = s2.p1;
    if (s2.p2 > s.p2)
        s.p2 = s2.p2;
    return s;
}

std::vector<segment> normalize(std::vector<segment> segs) {
    std::vector<segment> res;
    int total = segs.size();
//    on each iteration amount of segments decreases by 1
//    so total number on iterations equals size of vector with segments
    for (int it = 0; it < total; it++) {
        bool changed = false;
        for (int i = 1; i < segs.size(); i++) {
            if (overlap(segs[0], segs[i])) {
                changed = true;
                segs.push_back(new_segment(segs[0], segs[i]));
                segs.erase(segs.begin() + i, segs.begin() + i + 1);
                break;
            }
        }
        if (!changed) {
            res.push_back(segs[0]);
        }
        segs.erase(segs.begin(), segs.begin() + 1);
    }
    for (auto &u : res) {
        if (u.p1 > u.p2)
            std::swap(u.p1, u.p2);
    }
    std::sort(res.begin(), res.end());
    return res;
}

bool compare(std::vector<segment> s1, std::vector<segment> s2) {
    bool res = true;
    if (s1.size() != s2.size()) {
        res = false;
    } else {
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] == s2[i]) {
                continue;
            } else {
                res = false;
                break;
            }
        }
    }
    return res;
}

bool are_equal(std::vector<segment> segs1, std::vector<segment> segs2) {
    std::vector<segment> segs1_modified = normalize(segs1), segs2_modified = normalize(segs2);
    if (compare(segs1_modified, segs2_modified)) {
        return true;
    } else {
        return false;
    }
}
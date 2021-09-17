#include "main.h"

bool test_overlap() {
    if (!(overlap(segment(0, 0, 1, 1), segment(1, 1, 2, 2))
          && overlap(segment(0, 0, 3, 3), segment(1, 1, 2, 2))
          && overlap(segment(0, 0, 0, 2), segment(0, 1, 0, 3)))) {
        return false;
    } else {
        return true;
    }
}

bool test_normalize() {
    if (!(compare(normalize({segment(0, 0, 1, 1), segment(1, 1, 2, 2), segment(0, 2, 1, 1), segment(1, 1, 2, 0)}),
                  {segment(0, 0, 2, 2), segment(0, 2, 2, 0)})
          && compare(normalize(
            {segment(0, 0, 1, 1), segment(1, 1, 2, 2), segment(2, 2, 3, 3), segment(3, 3, 4, 4), segment(4, 4, 5, 5)}),
                     {segment(0, 0, 5, 5)}))) {
        return false;
    } else {
        return true;
    }
}
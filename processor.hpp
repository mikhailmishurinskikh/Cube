#pragma once

#include "constants.hpp"
#include <QVector>
#include <QQueue>

namespace processor {

struct Position {
    int block;
    int orientation;
};

class RubickState {
public:
    RubickState();
    void makeTurn(rotation rotation);
    bool isSolved();

    bool operator==(const RubickState& other) const;

private:
    Position positions[7];
};

struct Node {
    RubickState state;
    QVector<rotation> path;
};

QVector<rotation> findSolution(RubickState start);

}

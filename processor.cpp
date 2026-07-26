#include "processor.hpp"

#include <QDebug>

processor::RubickState::RubickState()
{
    for (int i{}; i < 7; i++) {
        positions[i].block = i;
        positions[i].orientation = 0;
    }
}

void processor::RubickState::makeTurn(rotation rotation)
{
    switch (rotation) {
        case rotation::Right: {
            Position pos0 = positions[0];
            
            positions[0].block = positions[1].block;
            positions[0].orientation = (positions[1].orientation + 2) % 3;

            positions[1].block = positions[5].block;
            positions[1].orientation = (positions[5].orientation + 1) % 3;

            positions[5].block = positions[4].block;
            positions[5].orientation = (positions[4].orientation + 2) % 3;

            positions[4].block = pos0.block;
            positions[4].orientation = (pos0.orientation + 1) % 3;
            break;
        }

        case rotation::Bottom: {
            Position pos0 = positions[0];

            positions[0] = positions[1];
            positions[1] = positions[2];
            positions[2] = positions[3];
            positions[3] = pos0;
            break;
        }

        case rotation::Front: {
            Position pos1 = positions[1];

            positions[1].block = positions[2].block;
            positions[1].orientation = (positions[2].orientation + 2) % 3;

            positions[2].block = positions[6].block;
            positions[2].orientation = (positions[6].orientation + 1) % 3;

            positions[6].block = positions[5].block;
            positions[6].orientation = (positions[5].orientation + 2) % 3;

            positions[5].block = pos1.block;
            positions[5].orientation = (pos1.orientation + 1) % 3;
            break;
        }

        default: break;

            
    }
}

bool processor::RubickState::isSolved()
{
    for (int i{}; i < 7; i++) {
        if ((positions[i].block != i) || (positions[i].orientation != 0)) {
            return false;
        }
    }

    return true;
}

bool processor::RubickState::operator==(const RubickState &other) const
{
    for (int i = 0; i < 7; i++) {
        if (positions[i].block != other.positions[i].block) return false;
        if (positions[i].orientation != other.positions[i].orientation) return false;
    }
    return true;
}


QVector<rotation> processor::findSolution(RubickState start)
{
    if (start.isSolved()) {
        return {};
    }
    
    QQueue<Node> queue;
    queue.enqueue({start, {}});

    while (!queue.isEmpty()) {
        Node current = queue.dequeue();
        
        for (rotation rot : {rotation::Right, rotation::Bottom, rotation::Front}) {
            Node next = current;
            next.state.makeTurn(rot);
            next.path.append(rot);
            
            if (next.state.isSolved()) {
                return next.path;
            }
            
            queue.enqueue(next);
        }
    }
}

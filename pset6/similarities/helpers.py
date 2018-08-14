from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    lena, lenb = len(a) + 1, len(b) + 1

    matrix = [[() for x in range(lenb)] for y in range(lena)]

    for i in range(lena):
        for j in range(lenb):
            if i == 0:
                if j == 0:
                    t = (j, None)
                else:
                    t = (j, Operation.INSERTED)
            elif j == 0:
                t = (i, Operation.DELETED)
            else:
                top = matrix[i - 1][j][0] + 1
                right = matrix[i][j - 1][0] + 1
                angel = matrix[i - 1][j - 1][0]
                if a[i - 1] != b[j - 1]:
                    angel += 1
                if angel <= top and angel <= right:
                    t = (angel, Operation.SUBSTITUTED)
                elif right <= top and right <= angel:
                    t = (right, Operation.DELETED)
                elif top <= angel and top <= right:
                    t = (top, Operation.INSERTED)
            matrix[i][j] = t

    return matrix

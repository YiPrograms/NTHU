#include <iostream>
#include <algorithm>

using namespace std;


struct Node {
    long long x, y;
    Node *next, *prev;

    Node(long long x, long long y, Node *next, Node *prev): x(x), y(y), next(next), prev(prev) { }
};

Node *head, *tail;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op[0] == 'H') { // House
            long long x, y;
            cin >> x >> y;

            Node **now = &head;
            while (*now && ( (*now)->y < y || ((*now)->y == y && (*now)->x < x) ))
                now = &(*now)->next;

            if (*now && (*now)->x == x && (*now)->y == y)
                continue;

            Node *tmp = *now;
            *now = new Node(x, y, *now, nullptr);
            if (tmp == nullptr) {
                (*now)->prev = tail; 
                tail = *now;
            } else {
                (*now)->prev = tmp->prev;
                tmp->prev = *now;
            }

        } else if (op[0] == 'B') { // Bomb
            long long x, y;
            cin >> x >> y;

            Node **now = &head;
            while (*now) {
                if (abs((*now)->x - x) + abs((*now)->y - y) <= 1) {
                    Node *tmp = *now;
                    *now = (*now)->next;

                    if (*now)
                        (*now)->prev = tmp->prev;
                    else
                        tail = tmp->prev;

                    delete tmp;
                } else {
                    now = &(*now)->next;
                }
            }
        } else if (op[5] == 'F') { // PrintFront
            cout << "PrintFront\n";
            Node *now = head;
            while (now) {
                cout << '(' << now->x << "," << now->y << ")\n";
                //cout << '(' << now->x << "," << now->y << ") " << now << " " << now->prev << " " << now->next << "\n";;
                now = now->next;
            }

        } else { // PrintEnd
            cout << "PrintEnd\n";
            Node *now = tail;
            while (now) {
                cout << '(' << now->x << "," << now->y << ")\n";
                //cout << '(' << now->x << "," << now->y << ") " << now << " " << now->prev << " " << now->next << "\n";;
                now = now->prev;
            }
        }
    }
}

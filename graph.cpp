#include <iostream>
#include <string>
// #include <vector>
#include <time.h>
#include <chrono>
#include <random>

using namespace std;

int parent(int c) {

    if (c % 2 == 0) {
        return (c / 2) - 1;
    } else {
        return (c / 2);
    }

}

bool isLeaf(int val, int size) {

    if (size <= val) {
        return true;
    } else {
        return false;
    }

    return false;
}

void shiftUp (int val, int H[], int D[]) {

    int parVal = parent(val);

    // if (val == 0) {
    //     return;
    // }

    if ((D[H[parVal]] < D[H[val]]) && val != 0) {
        swap(H[parVal], H[val]);
        // swap(D[parVal], D[val]);
        // swap
        shiftUp(parVal, H, D);
    } else {
        return;
    }
}

void shiftDown (int val, int size, int H[], int D[]) {

    int left = (2 * val + 1);
    int right = (2 * val + 2);

    if (isLeaf(left, size) == true) {
        // cout << "Size: " << size << endl;
        return;
    } else {
        int max = val;
        if (D[H[left]] > D[H[val]]) {
            max = left;
        }

        if ((D[H[right]] > D[H[max]]) && !isLeaf(right, size)) {
            max = right;
        }

        if (max != val) {
            swap(H[val], H[max]);
            shiftDown(max, size, H, D);
        }
    }
}

void insert(int vertex, int weight, int &size, int H[], int D[]) {

    // adjListNode* temp = new adjListNode;
    // temp = vertex;

    // D[H[size]] = weight;
    // H[size] = vertex;
    // shiftUp(size, H, D);
    // size++;

    // size++;

    H[size] = vertex;
    D[H[size]] = weight;

    // H[size] = vertex;
    shiftUp(size, H, D);
    size++;
}

void remove(int key, int &size, int H[], int D[]) {

    int pos;

    for (int i = 0; i < size; i++) {
        if (H[i] == key) {
            pos = i;
        }
    }

    H[pos] = H[size - 1];
    // cout << "Size before decrement: " << size << endl;

    size --;
    // cout << "Size aftfer decrement: " << size << endl;

    int parent_ = parent(pos);

    if (pos == 0 || H[pos] < H[parent_]) {
        shiftDown(pos, size, H, D);
    } else {
        // cout << "Hey!" << endl;
        shiftUp(pos, H, D);
    }

    // shiftDown(pos);
    // size--;

}

int max(int H[]) {
    return H[0];
}

void arrPrint(int size, int H[]) {
    for (int i = 0; i < size; i++) {
        cout << H[i] << " ";
    }
    cout << endl;
}


struct adjListNode {

    int data;
    struct adjListNode* next;
    int weight;

    // adjListNode() {
    //     data = 0;
    //     weight = 0;
    // }

};


struct adjList {

    struct adjListNode *head;
};

class graph {

    private: 

        int vertex;
        adjList* list;

    public:

        graph(int vertex) {

            this->vertex = vertex;
            list = new adjList[vertex];

            for (int i = 0; i < vertex; i++) {

                list[i].head = NULL;
            }
        }

        void appendEdge(int src, int dest, int weight) {

            adjListNode* temp = new adjListNode;

            temp->data = dest;
            temp->next = NULL;
            temp->next = list[src].head;

            temp->weight = weight;

            // temp->weight = weight;

            list[src].head = temp;

            // free(temp);
            temp = new adjListNode;

            temp->data = src;
            temp->next = NULL;
            temp->next = list[dest].head;

            temp->weight = weight;
            
            list[dest].head = temp;

            // free(temp);
        }

        // void printGraph() {

        //     int vertex;

        //     for (vertex = 0;)
        // }

        void print() {

            int v;

            for (v = 0; v < vertex; ++v) {

                adjListNode* temp = list[v].head;
                cout<<"\n Adjacency list of vertex "<<v<<"\n head ";
                int count = 0;
                while (temp)
                {
                    cout<<"-> "<<temp->data;
                    temp = temp->next;
                    count++;
                }
                cout << endl;
                cout << "Degrees: " << count << endl;

                if (v == 2) {
                    break;
                }
                // cout<<endl;
            }
        }

        bool edgeExists(int src, int dest) {

            adjListNode* temp = list[src].head;

            while (temp) {
                if (temp->data == dest) {
                    return true;
                } else {
                    temp = temp->next;
                }
            }
            return false;
        }

        int getDegree(int vert) {

            adjListNode* temp = list[vert].head;
            int count = 0;

            while (temp) {
                temp = temp->next;
                count++;
            }

            return count;
            // for (int i = 1; i<= vertex; ++i) {
            //     adjListNode* temp = list[i].head;
            //     int count = 0;
            // }
        }

        int getVertex() {
            return vertex;
        }

        // void dijkstraNoHeap(int src, int dest) {

        //     int status[vertex];
        //     int dad[vertex];
        //     int bw[vertex];

        //     enum NodeStatus {UNSEEN, INTREE, FRINGE};

        //     for (int i = 0; i < vertex; i++) {

        //         status[i] = UNSEEN;
        //         dad[i] = FRINGE;
        //         bw[i] = INT_MAX;
        //     }

        //     status[src] = INTREE;
        //     bw[src] = UNSEEN;
        //     dad[src] = src;

    
        // }

        void dijkstraNoHeap(int src, int dest) {

            int status[vertex];
            int dad[vertex];
            int bw[vertex];
            int count = 0;

            enum NodeStatus {UNSEEN, INTREE, FRINGE};

            for (int v = 0; v < vertex; v++) {
                status[v] = UNSEEN;
            }

            status[src] = INTREE;

            adjListNode* temp = list[src].head;

            while (temp) {

                int edge = temp->data;
                
                status[edge] = FRINGE;
                dad[edge] = src;
                bw[edge] = temp->weight;
                
                count++;

                // cout << "Edge: " << edge << endl;
                // cout << "Weight: " << bw[edge] << endl;

                temp = temp->next;

                // break;

            }

            // for (int i = 0; i < vertex; i++) {
            //     if (status[i] == FRINGE) {
            //         cout << i << " ";
            //     }
            //     // cout << endl;
            // }
            // cout << endl;

            // return;


            while (count != 0) {

                int maxWgt = 0;
                int v;
                for (int i = 0; i < vertex; i++) {
                    if (status[i] == FRINGE) {

                        if (bw[i] > maxWgt) {
                        
                            maxWgt = bw[i];
                            v = i;
                            // cout << "Vertex: " << v << " Weight: " << maxWgt << endl;

                        }
                    }
                }

                // cout << "Vertex: " << v << " Weight: " << maxWgt << endl;
                // cout << maxWgt << endl;
                // return;

                status[v] = INTREE;
                count--;

                adjListNode* temp = list[v].head;

                while (temp) {

                    int edge = temp->data;

                    if (status[edge] == UNSEEN) {
                        status[edge] = FRINGE;
                        count++;
                        bw[edge] = min(bw[v], temp->weight);
                        dad[edge] = v;
                    } else if ((status[edge] == FRINGE) && (bw[edge] < min(bw[v], temp->weight))) {
                        bw[edge] = min(bw[v], temp->weight);
                        dad[edge] = v;
                    }

                    temp = temp->next;
                }

            }

            if (status[dest] != INTREE) {
                cout << "No Path from S - T!" << endl;
            } else {
                int x = dest;

                // cout << x << endl;
                while (x != src) {
                    cout << x << endl;
                    x = dad[x];
                }

                cout << x << endl;
            }


        }


        void dijkstraWHeap(int src, int dest) {

            int status[vertex];
            int dad[vertex];
            int bw[vertex];
            int H[vertex];
            int D[vertex];
            int P[vertex];
            int size = 0;
            int count = 0;

            enum NodeStatus {UNSEEN, INTREE, FRINGE};

            for (int v = 0; v < vertex; v++) {
                status[v] = UNSEEN;
            }

            status[src] = INTREE;

            adjListNode* temp = list[src].head;

            while (temp) {

                int edge = temp->data;
                
                status[edge] = FRINGE;
                dad[edge] = src;
                bw[edge] = temp->weight;
                // fringeHeap.insert(temp);
                insert(temp->data, temp->weight, size, H, D);

                // cout << "Vertex: " << edge << " Weight: " << temp->weight << endl;

                temp = temp->next;

            }

            cout << endl;

            // arrPrint(size, D);
            // arrPrint(size, H);
            // arrPrint(size, D);

            // for (int i = 0; i < size; i++) {
            //     cout << D[H[i]] << " ";
            // }
            // cout << endl;

            // return;





            while (size > 0) {

                // int maxWgt = 0;
                // for (int i = 0; i < vertex; i++) {
                //     if (status[i])

                // }

                // for (int i = 0; i < 10; i++) {
                //     cout << D[H[i]] << " ";
                // }

                // cout << endl;

                int v = max(H);

                // cout << v << endl;
                // return;
                // for (int i = 0; i < vertex; i++) {
                //     if (status[i] == FRINGE) {

                //         if (bw[i] > maxWgt) {
                //             maxWgt = bw[i];
                //             v = i;
                //         }
                //     }
                // }

                status[v] = INTREE;
                remove(v, size, H, D);
                // count--;

                adjListNode* temp = list[v].head;

                while (temp) {

                    int edge = temp->data;

                    if (status[edge] == UNSEEN) {
                        status[edge] = FRINGE;
                        // count++;
                        bw[edge] = min(bw[v], temp->weight);
                        dad[edge] = v;
                        insert(edge, temp->weight, size, H, D);
                    } else if ((status[edge] == FRINGE) && (bw[edge] < min(bw[v], temp->weight))) {
                        remove(edge, size, H, D);
                        bw[edge] = min(bw[v], temp->weight);
                        insert(edge, temp->weight, size, H, D);
                        dad[edge] = v;
                    }

                    temp = temp->next;
                }

            }

            if (status[dest] != INTREE) {
                cout << "No bloody path!" << endl;
            } else {
                int x = dest;
                while (x != src) {
                    cout << x << endl;
                    x = dad[x];
                }

                cout << x << endl;
            }


        }

        void kruskal() {



        }

        adjList* getArray() {
            return list; 
        }


};

// int largestVal(int values[]) {

//     int maxVal = values[0];
//     int valArrSize = sizeof(values)/sizeof(values[0]);

//     for (int i = 1; i < valArrSize; i++) {
//         if (values[i] > maxVal) {
//             maxVal = values[i]; 
//         }
//     }

//     return maxVal;
// }


void generateGraph1(graph g1) {

    // g1(5000);

    srand(time(0));

    for (int i = 0; i < 4999 ; i++) {

        int randWgt = rand() % 5000 + 1;
        g1.appendEdge(i, i+1, randWgt); // creates 2500
    }

    for (int i = 0; i < (10001); i++) {

        loopStart:

            int randSrc = rand() % 5000;
            int randDest = rand() % 5000;
            int randWgt = rand() % 5000;


            if (g1.edgeExists(randSrc, randDest)) {
                goto loopStart;
            } else {
                g1.appendEdge(randSrc, randDest, randWgt);
            }

      
    }
}



void generateGraph2(graph g2) {

    srand(time(0));

    for (int i = 0; i < 4999 ; i++) {

        int randWgt = rand() % 5000 + 1;
        g2.appendEdge(i, i+1, randWgt); // creates 2500
    }

    for (int i = 0; i < 5000; ++i) {

        int src = i;

        for (int j = 0; j < (500); ++j) {

            loopStart:

                int randDest = rand() % 5000;
                int randWgt = rand() % 5000;

                if (g2.edgeExists(src, randDest) || src == randDest )  {

                    goto loopStart;
                } else {

                    g2.appendEdge(src, randDest, randWgt);

                }
        }
    } 
}


// void generateGraph2(graph g2)


int main () {

    srand(time(0));

    graph g1(5000);
    generateGraph1(g1);

    

    // g1.dijkstraNoHeap(2, 100);
    // cout << endl;
    // g1.dijkstraWHeap(2, 100);


    // g1.print();
    graph g2(5000);
    generateGraph2(g2);

    g2.dijkstraNoHeap(2, 100);
    cout << endl;
    g2.dijkstraWHeap(2, 100);

    // cout << "Here" << endl;

    // g1.dijkstraNoHeap(1, 10);

    // int array[5] = {21, 5, 30, 10, 1};
    // maxheap h1(6);

    // h1.insert(231);
    // h1.insert(250);
    // h1.insert(245);
    // h1.insert(320);
    // h1.insert(220);

    // h1.displayHeap();

    // h1.remove(320);

    // h1.displayHeap();

    // int vert = 5000;
    // int size = 0;

    // int H[vert];
    // int D[vert];
    // int P[vert];

    // int temp = 5;

    // for (int i = 0; i < 6; i++) {
    //     insert(i, temp, size, H, D);
    //     temp+=5;
    // }

    // // for (int i = 0; i < 6; i++) {
    // //     cout << D[i] << endl;
    // // }

    // print(size, D);
    // print(size, H);
    // print(size, D[H]);

    // for (int i = 0; i < 6; i++) {
    //     cout << H[i] << " ";
    //     // if (i == 10) {
    //     //     break;
    //     // }
    // }
    // cout << endl;

    // for (int i = 0; i < size; i++) {
    //     cout << D[H[i]] << " ";
    // }
    // cout << endl;

    // remove(0, size, H, D);

    // for (int i = 0; i < size; i++) {
    //     cout << H[i] << " ";
    //     // if (i == 10) {
    //     //     break;
    //     // }
    // }
    // cout << endl;


    // for (int i = 0; i < size; i++) {
    //     cout << D[H[i]] << " ";
    // }
    // cout << endl;

    // cout << H[6] << endl;




    // int randSrc = rand() % 5000;
    // int randDest = rand() % 5000;

    // cout << "Src: " << randSrc << endl;
    // cout << "Dest: " << randDest << endl;
    // cout << endl;


    // g1.dijkstraNoHeap(randSrc, randDest);









    // g1.print();

    // g1.print();

    

    // int g1Sum = 0;
    // for (int i = 0; i < 5000; i++) {
    //     g1Sum += g1.getDegree(i);
    // }
    // cout << "Graph 1 SUM: " << g1Sum << endl;

    // int g2Sum = 0;
    // for (int i = 0; i < 5000; i++) {
    //     g2Sum += g2.getDegree(i);
    // }
    // cout << "Graph 2 SUM: " << g2Sum << endl;

    // return 0;



}



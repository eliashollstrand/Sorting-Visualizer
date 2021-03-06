// Input:
// S = Selection sort
// B - Bubble sort

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define LOG(x) cout << x << endl;

using namespace std;

bool selection = false;
bool bubble = false;

class Rect {
    public:
        float height;
        Rect(float h) {
            this->height = h;
        }
};

float randomNumber(float min, float max) {
    return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

void display(int i, Rect rect) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex2f(-0.91 + i * 0.1, rect.height);
    glVertex2f(-0.91 + i * 0.1, -1);
    glVertex2f(-1 + i * 0.1, -1);
    glVertex2f(-1 + i * 0.1, rect.height);
    glEnd();
}

vector<Rect> selectionSort(vector<Rect> v) {
    for (int i = 0; i < v.size(); i++) {
        float min = v[i].height;
        int minIndex = i;
        for (int j = i; j < v.size(); j++) {
            if (v[j].height < min) {
                min = v[j].height;
                minIndex = j;
            }
        }
        swap(v[i], v[minIndex]);
    }

    return v;
}

vector<Rect> bubbleSort(vector<Rect> v) {
    for (int i = 0; i < v.size(); i++) {
        int numberOfSwaps = 0;

        for (int j = 0; j < v.size() - 1; j++) {
            if (v[j].height > v[j + 1].height) {
                swap(v[j], v[j + 1]);
                numberOfSwaps++;
            }
        }

        if (numberOfSwaps == 0) {
            break;
        }
    }
    return v;
}

// Run algorithm on input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_S && action == GLFW_PRESS) {
        selection = !selection; // Assigns the opposite value to shouldSort
        if(selection)
            LOG("Sorted with algorithm: Selection Sort");
    } else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        bubble = !bubble; // Assigns the opposite value to shouldSort
        if (bubble)
            LOG("Sorted with algorithm: Bubble Sort");
    }
}

int main() {
    LOG("Sorting Algorithms:\n");
    LOG("Selection Sort (S)");
    LOG("Bubble Sort (B)\n");

    GLFWwindow* window;

    if (!glfwInit()) 
        return -1;

    window = glfwCreateWindow(1200, 600, "Sorting Visualizer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    vector<Rect> vector;
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        float height = randomNumber(-1, 1);
        Rect r(height);
        vector.push_back(r);
    }
   
    std::vector<Rect> v;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if(selection || bubble) {
            if (selection)
                v = selectionSort(vector);
            else if (bubble)
                v = bubbleSort(vector);

            for (int i = 0; i < v.size(); i++) {
                Rect rect = v[i];
                display(i, rect);
            }
        } else {
            for (int i = 0; i < vector.size(); i++) {
                Rect rect = vector[i];
                display(i, rect);
            }
        }

        glfwSetKeyCallback(window, key_callback);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
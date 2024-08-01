#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#define INF 9999

// Node struct represents a vertex in a graph
struct node
{
    int id;
    int N;
    int air; // Status of the link, whether it's by air (1) or not (0)
    node* next;

    node()
    {
        N = 0;
        id = 0;
        air = 0;
        next = nullptr;
    }

    // Constructor
    node(int i, int a)
    {
        N = 0;
        id = i;
        air = a;
        next = nullptr;
    }

    // Destructor
    ~node()
    {
    }
};

// Queue
struct Queue
{
    node* head;

    // Constructor
    Queue()
    {
        head = nullptr;
    }

    // Push function
    void push(int e)
    {
        // Create node
        node* use = new node(e, 0);
        node* curr = head;
        // Check if Queue is empty or not
        if (curr == nullptr)
        {
            head = use;
        }
        else
        {
            while (curr->next)
            {
                curr = curr->next;
            }
            curr->next = use;
        }
    }

    // Pop function
    void pop()
    {
        if (!isempty())
        {
            node* use = head;
            head = head->next;
            delete use;
        }
    }

    // Peek function
    int peek()
    {
        if (!isempty())
        {
            return head->id;
        }
        return -1;
    }

    // Empty function
    bool isempty()
    {
        if (head == nullptr)
        {
            return true;
        }
        return false;
    }

    // Destructor
    ~Queue()
    {
        while (!isempty())
        {
            pop();
        }
    }
};

//reverse queue
void reverse_queue(Queue& result)
{
    if (result.isempty())
    {
        return;
    }
    int use = result.peek();
    result.pop();
    reverse_queue(result);
    result.push(use);
}

// Struct for an order
struct Order
{
    string name;
    int node_loc;
    int div_time;
    Order()
    {
        name = "";
        node_loc = 0;
        div_time = 0;
    }

    Order(string n, int nl, int dt)
    {
        name = n;
        node_loc = nl;
        div_time = dt;
    }
};

// Struct to represent a restaurant
struct Restaurant
{
    string name;
    Order* orders; // Array to store orders
    int node_loc;
    int N;
    int num_orders; // Number of orders

    Restaurant()
    {
        name = "";
        orders = nullptr;
        node_loc = 0;
        N = 0;
        num_orders = 0;
    }

    Restaurant(string nam, int nl, int no, int n)
    {
        name = nam;
        node_loc = nl;
        N = n;
        num_orders = no;
        orders = new Order[num_orders];
    }

    void output()
    {
        cout << "Restaurant node value: " << node_loc << endl;
        for (int i = 0; i < num_orders; i++)
        {
            cout << "Order " << i + 1 << " node value: " << orders[i].node_loc << endl;
        }
    }
};

// Struct for graph
struct Graph
{
    // N = N x N size of grid
    int N;
    node** grid;

    Graph()
    {
        N = 0;
        grid = nullptr;
    }

    Graph(int n)
    {
        N = n;
        //allocating heap memory
        grid = new node * [N];
        for (int i = 0; i < N; ++i)
        {
            grid[i] = nullptr;
        }

        for (int i = 0; i < N; ++i)
        {
            if (i != N - 1)
            {
                add_edge(i, i + 1, 0);
            }
        }
    }

    //add edge to graph function
    void add_edge(int from, int to, int a)
    {
        //creating vertex
        //here (a) is the status of  the link is it by air(1) or not(0)
        node* use = new node(to, a);

        //adding new node at start of links(list) of the given city(from)
        use->next = grid[from];
        grid[from] = use;
    }

    int minDistance(int dist[], bool visited[], int V)
    {
        int minDist = INF, minIndex = -1;
        for (int v = 0; v < V; ++v)
        {
            if (!visited[v] && dist[v] <= minDist)
            {
                minDist = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    int dijkstra(int** graph, int source, int target, int V, int* deliveryTimes)
    {
        bool* visited = new bool[V];
        int* dist = new int[V];

        for (int i = 0; i < V; ++i)
        {
            visited[i] = false;
            dist[i] = INF;
        }

        dist[source] = 0;

        for (int count = 0; count < V - 1; ++count)
        {
            int u = -1;
            int minDist = INF;

            // Find the vertex with the minimum distance value
            for (int v = 0; v < V; ++v)
            {
                if (!visited[v] && dist[v] < minDist)
                {
                    u = v;
                    minDist = dist[v];
                }
            }

            if (u == -1)
                break;

            visited[u] = true;

            // Update distances of adjacent vertices
            for (int v = 0; v < V; ++v)
            {
                if (!visited[v] && graph[u][v] != -1 && dist[u] != INF
                    && dist[u] + graph[u][v] < dist[v])
                {
                    // Check delivery time constraint
                    if (dist[u] + graph[u][v] <= deliveryTimes[v])
                    {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
            }
        }

        int result = dist[target];
        delete[] visited;
        delete[] dist;
        return result;
    }

    void PrintGraph()
    {
        int count = 1;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << setw(3) << count++ << " ";
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        for (int i = 0; i < N; ++i)
        {
            node* current = grid[i];
            while (current)
            {
                node* use = current;
                current = current->next;
                delete use;
            }
        }
        delete[] grid;
    }
};

void processFile(const string& testfile)
{
    ifstream file(testfile); // Open the file

    if (!file.is_open())
    {
        cout << "File " << testfile << " is not opening or not opened " << endl;
        return;
    }

    int tests;
    file >> tests;

    for (int t = 0; t < tests; t++)
    {
        cout << "Test Case " << t + 1 << ":" << endl;

        //N= number of the graph N x N
        int N, num_riders, num_rest;
        file >> N >> num_riders >> num_rest;
        Graph g(N);
        Graph g1;
        g.PrintGraph();
        cout << "\nRiders: " << num_riders << "\nRestaurants: " << num_rest << endl;

        // Read restaurants and orders
        Restaurant* rest;
        rest = new Restaurant[num_rest];
        for (int i = 0; i < num_rest; ++i)
        {
            string rest_name;
            int rest_loc, num_orders;
            file >> rest_name >> rest_loc >> num_orders;
            cout << "Restaurant " << i + 1 << ": " << rest_name << "\nLocation: " << rest_loc << "\nNumber of Orders: " << num_orders << endl;

            rest[i] = Restaurant(rest_name, rest_loc, num_orders, N);

            for (int j = 0; j < num_orders; j++)
            {
                string order_name;
                int order_location, div_time;
                file >> order_name >> order_location >> div_time;
                cout << "Order " << j + 1 << ": " << order_name << "\nLocation: " << order_location << "\nDelivery Time: " << div_time << endl;

                rest[i].orders[j] = Order(order_name, order_location, div_time);

            }
            rest[i].output();

        }
        //Graph g2;
        //g2.shortest_path();
    }

    file.close(); // Closing the file
}

int main()
{
    // txt file for text cases
    processFile("test.txt");
    return 0;
}
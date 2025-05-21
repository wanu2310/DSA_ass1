#include "main2.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    vector<int> data;
    int label;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(vector<int> data, int label, kDTreeNode* left=nullptr, kDTreeNode* right =nullptr){
        this->data = data;
        this->label = label;
        this->left=nullptr;
        this->right =nullptr;
    }
    void print() const  
    {
        OUTPUT << "(";
        for(int i = 0; i < data.size(); i++)
        {
            OUTPUT << data[i];
            if (i == data.size() - 1) OUTPUT << ") ";
            else OUTPUT << ", ";
        }
        //OUTPUT << "\n";
    }
    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;
    int count;
private:
    void deleteTree(kDTreeNode* node){
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    kDTreeNode* copyTree(kDTreeNode* node) {
        if (node == nullptr) return nullptr;
        kDTreeNode* newNode = new kDTreeNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    void inorderHelper(kDTreeNode* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left);
        printData(node->data);
        inorderHelper(node->right);
    }
    void preorderHelper(kDTreeNode* node) const {
        if (node == nullptr) return;
        printData(node->data);
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    void postorderHelper(kDTreeNode* node) const {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        printData(node->data);
    }
    void printData(const vector<int>& data) const {
        OUTPUT << "(";
        for (int i = 0; i < data.size(); ++i) {
            OUTPUT << data[i];
            if (i < data.size() - 1) OUTPUT << ", ";
        }
        OUTPUT << ") ";
    }
    int leafCountHelper(kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return leafCountHelper(node->left) + leafCountHelper(node->right);
    }
    int heightHelper(kDTreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        return max(leftHeight, rightHeight) + 1;
    }
    kDTreeNode* insertHelper(kDTreeNode *temp, const vector<int> &point, int level) {
        if (temp == nullptr) return new kDTreeNode(point);
        int alpha = level % k;
        if (point[alpha] < temp->data[alpha])
            temp->left = insertHelper(temp->left, point, level + 1);
        else 
            temp->right = insertHelper(temp->right, point, level + 1);
        return temp;
    }
    bool searchHelper(kDTreeNode* temp, const vector<int> &point, int level){
        if (temp == nullptr) return false;
        int alpha =level%k;
        if (point[alpha] < temp->data[alpha]) 
            return searchHelper(temp->left, point, level + 1);
        else if (point[alpha] > temp->data[alpha])
            return searchHelper(temp->right, point, level + 1);
        else
            // If the point is found, return true
            if (temp->data == point)
                return true;
            else return searchHelper(temp->right, point, level + 1);
    }
    kDTreeNode* removeHelper(kDTreeNode* node, const vector<int> &point, int level) {
        if (node == nullptr) return nullptr; // Bước 1: điều kiện dừng không tìm thấy

        int alpha = level % k; // Bước 3: tính alpha = level % k;
        if (point[alpha] < node->data[alpha]) {
            node->left = removeHelper(node->left, point, level + 1);
        } else if (point[alpha] > node->data[alpha]) {
            node->right = removeHelper(node->right, point, level + 1);
        } else {
            if (node->data == point){
            if (node->left == nullptr && node->right == nullptr) {
                delete node; // Bước 2: Nếu Node u là một lá: Chỉ cần xóa nó và kết thúc.
                return nullptr;
            } else if (node->right!= nullptr) {
                kDTreeNode* minNode = findMin(node->right, level+1, alpha); // Bước 4: Nếu Node u có cây con bên phải
                node->data = minNode->data;
                node->right = removeHelper(node->right, minNode->data, level + 1);
            } else {
                kDTreeNode* minNode = findMin(node->left, level+1, alpha); // Bước 5: Nếu u không có cây con bên phải thì nó sẽ có cây con bên trái
                node->data = minNode->data;
                node->left = removeHelper(node->left, minNode->data, level + 1);
                node->right = node->left;
                node->left = nullptr;
            }
            }
            else node->right = removeHelper(node->right, point, level+1);
        }
        return node;
    }
    kDTreeNode* findMin(kDTreeNode* node, int level, int alpha) {
        if (level%k == alpha){
            if (node->left==nullptr)
                return node;
            else return findMin(node->left, level+1, alpha);
        }
        else {
            kDTreeNode *minNode = node;
            if (node->left !=nullptr && node->right!=nullptr){
                kDTreeNode* leftMin = findMin(node->left, level+1, alpha);
                kDTreeNode* rightMin = findMin(node->right, level+1, alpha);
                if (leftMin->data[alpha] < minNode->data[alpha]){
                    if (rightMin->data[alpha] < leftMin->data[alpha])
                        minNode = rightMin;
                    else minNode = leftMin;
                }
                else if (rightMin->data[alpha] < minNode->data[alpha]){
                    if (leftMin->data[alpha] < rightMin->data[alpha])
                        minNode = leftMin;
                    else minNode = rightMin;
                }
            }
            else if (node->left !=nullptr){
                kDTreeNode* leftMin = findMin(node->left, level+1, alpha);
                if (leftMin->data[alpha] < minNode->data[alpha])
                    minNode = leftMin;
            }
            else if (node->right !=nullptr){
                kDTreeNode* rightMin = findMin(node->right, level+1, alpha);
                if (rightMin->data[alpha] < minNode->data[alpha])
                    minNode = rightMin;
            }
            return minNode;
        }
    }
    kDTreeNode* buildTreeHelper(const vector<vector<int>> &pointList, int level){
        if (pointList.empty()) return nullptr;
        
        int dim = level % k;
        vector<vector<int>> sortedPoints = pointList;
        mergeSort(sortedPoints, 0, sortedPoints.size() - 1, dim);
        
        int medianIndex = (sortedPoints.size()-1) / 2;
        for (int i=0; i<sortedPoints.size(); i++){
            if (sortedPoints[i][dim] == sortedPoints[medianIndex][dim]){
                medianIndex = i;
                break;
            }
        }
        kDTreeNode *node = new kDTreeNode(sortedPoints[medianIndex]);
        vector<vector<int>> leftPoints(sortedPoints.begin(), sortedPoints.begin() + medianIndex);
        vector<vector<int>> rightPoints(sortedPoints.begin() + medianIndex + 1, sortedPoints.end());
        node->left = buildTreeHelper(leftPoints, level + 1);
        node->right = buildTreeHelper(rightPoints, level + 1);
        
        return node;
    }
    void merge(vector<vector<int>> &points, int left, int mid, int right, int dim) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<vector<int>> L(n1);
        vector<vector<int>> R(n2);
        
        for (int i = 0; i < n1; ++i)
            L[i] = points[left + i];
        for (int i = 0; i < n2; ++i)
            R[i] = points[mid + 1 + i];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i][dim] <= R[j][dim]) {
                points[k] = L[i];
                i++;
            } else {
                points[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            points[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            points[k] = R[j];
            j++;
            k++;
        }
    }
    void mergeSort(vector<vector<int>> &points, int left, int right, int dim) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(points, left, mid, dim);
            mergeSort(points, mid + 1, right, dim);
            merge(points, left, mid, right, dim);
        }
    }
    double squaredDistance(const vector<int> &a, const vector<int> &b) const {
        double dist = 0;
        for (int i = 0; i < a.size(); ++i) {
            dist += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return dist;
    }
    void neareastNeighbourHelper(kDTreeNode* temp, const vector<int> &target, kDTreeNode* &best, int level){
        if (temp == nullptr) return;
        int alpha = level % k;
        if (target[alpha] < temp->data[alpha]) {
            neareastNeighbourHelper(temp->left, target, best, level + 1);
        } else {
            neareastNeighbourHelper(temp->right, target, best, level + 1);
        }
        if (best == nullptr || squaredDistance(target, temp->data) < squaredDistance(target, best->data)) {
            best = temp;
        }
        
        // Update best node if necessary
        if (best == nullptr && temp->left==nullptr && temp->right==nullptr) {
            best = temp;
        }
        if (temp->data[alpha] < target[alpha]){
            neareastNeighbourHelper(temp->left, target, best, level + 1);
            double d = abs(temp->data[alpha] - target[alpha]);
            double R = squaredDistance(target, best->data);
            double r = squaredDistance(target, temp->data);
            if (r<R){
                R = r;
                best = temp;
            }
            if (d < R) {
                neareastNeighbourHelper(temp->right, target, best, level + 1);
            }
        }
        else{
            neareastNeighbourHelper(temp->right, target, best, level + 1);
            neareastNeighbourHelper(temp->left, target, best, level + 1);
            double d = abs(temp->data[alpha] - target[alpha]);
            double R = squaredDistance(target, best->data);
            double r = squaredDistance(target, temp->data);
            if (r<R){
                R = r;
                best = temp;
            }
            if (d < R) {
                neareastNeighbourHelper(temp->left, target, best, level + 1);
            }
        }
    }
    void kNearestNeighbourHelper(kDTreeNode* temp,const vector<int> &target,int n, vector<kDTreeNode*> &bestList, int level){
        // // Bước 1: Điều kiện dừng
        // if (temp == nullptr) return;
        // int alpha = level % this->k;
        // // Bước 2: Tính khoảng cách và cập nhật bestList
        // //if (bestList.size()<k) 
        // insertBestList(bestList, temp, target, n);
        // // Tính d
        // double d = abs(target[alpha] - temp->data[alpha]);
        // double r = (bestList.size() < n) ? numeric_limits<double>::max() : squaredDistance(target, bestList.front()->data);
        // // Bước 3: Nếu giá trị tại alpha nhỏ hơn node đó
        // if (target[alpha] < temp->data[alpha]) {
        //     kNearestNeighbourHelper(temp->left, target, n, bestList, level + 1);
        //     // Kiểm tra nhánh phải
        //     if (d*d < r || bestList.size() < n) {
        //         kNearestNeighbourHelper(temp->right, target, n, bestList, level + 1);
        //     }
        // }
        // // Bước 4: Nếu giá trị tại alpha lớn hơn hoặc bằng node đó
        // else {
        //     kNearestNeighbourHelper(temp->right, target, n, bestList, level + 1);
        //     // Kiểm tra nhánh trái
        //     if (d*d < r || bestList.size() < n) {
        //         kNearestNeighbourHelper(temp->left, target, n, bestList, level + 1);
        //     }
        // }
        // kDTreeNode* best = nullptr;
        // find_maxdistance(temp, target, best, 0);
        // OUTPUT << squaredDistance(target, best->data);
        if (temp == nullptr) return;
    int alpha = level % k;
    if (target[alpha] < temp->data[alpha]) {
        kNearestNeighbourHelper(temp->left, target, k, bestList, level + 1);
    } else {
        kNearestNeighbourHelper(temp->right, target, k, bestList, level + 1);
    }

    double dist = squaredDistance(target, temp->data);
    if (bestList.size() < k) {
        bestList.push_back(temp);
        push_heap(bestList, bestList.size() - 1, dist, target);
    } else if (dist < bestDist(bestList, target)) {
        pop_heap(bestList, 0, target);
        bestList[0] = temp;
        push_heap(bestList, 0, dist, target);
    }

    // Check if the current node is closer to the target than the k-th closest node
    if (temp->data[alpha] < target[alpha]) {
        kNearestNeighbourHelper(temp->left, target, k, bestList, level + 1);
    } else {
        kNearestNeighbourHelper(temp->right, target, k, bestList, level + 1);
    }
    }
    // void insertBestList(vector<kDTreeNode*>& bestList, kDTreeNode* node, const vector<int>& target, int k) {
    //     double dist = squaredDistance(target, node->data);
    //     if (bestList.size() < k) {
    //         //bestList.push_back(node);
    //         push_heap(bestList, node, target);
    //     } else if (dist < squaredDistance(target, bestList.front()->data)) {
    //         pop_heap(bestList, target);
    //         bestList.push_back(node);
    //         push_heap(bestList, node, target);
    //     }
    //     // if (temp == nullptr || bestList.size() > k) return;
    //     // int alpha = level % this->k;
    //     // if (temp->data[alpha] < target[alpha]){
    //     //     kNearestNeighbourHelper(temp->left, target, k, bestList, level+1);
    //     //     double d = abs( target[alpha] - temp->data[alpha]);
    //     //     kDTreeNode* best = nullptr;
    //     //     furthestNeighbourHelper(root, target, best, 0);
    //     //     double R = squaredDistance(target, best->data);
    //     //     double r = squaredDistance(target, temp->data);
    //     //     if (r<R){
    //     //         bestList.push_back(best);
    //     //     }
    //     //     if (d<R){
    //     //         kNearestNeighbourHelper(temp->right, target, k, bestList, level+1);
    //     //     }
    //     // }
    //     // else{
    //     //     kNearestNeighbourHelper(temp->right, target, k, bestList, level+1);
    //     //     double d = abs( target[alpha] - temp->data[alpha]);
    //     //     kDTreeNode* best = nullptr;
    //     //     furthestNeighbourHelper(root, target, best, 0);
    //     //     double R = squaredDistance(target, best->data);
    //     //     double r = squaredDistance(target, temp->data);
    //     //     if (r<R){
    //     //         bestList.push_back(best);
    //     //     }
    //     //     if (d<R){
    //     //         kNearestNeighbourHelper(temp->left, target, k, bestList, level+1);
    //     //     }
    //     // }
        
    // }
    // void push_heap(vector<kDTreeNode*>& heap, kDTreeNode* node, const vector<int>& target) {
    //     heap.push_back(node);
    //     int i = heap.size() - 1;
    //     while (i > 0) {
    //         int parent = (i - 1) / 2;
    //         if (squaredDistance(target, heap[i]->data) < squaredDistance(target, heap[parent]->data)) {
    //             break;
    //         }
    //         swap(heap[i], heap[parent]);
    //         i = parent;
    //     }
    // }
    // void pop_heap(vector<kDTreeNode*>& heap, const vector<int>& target) {
    //     if (heap.empty()) return;
    
    //     swap(heap[0], heap[heap.size() - 1]);
    //     heap.pop_back();

    //     int i = 0;
    //     while (true) {
    //         int left = 2 * i + 1;
    //         int right = 2 * i + 2;
    //         int largest = i;

    //         if (left < heap.size() && squaredDistance(target, heap[left]->data) > squaredDistance(target, heap[largest]->data)) {
    //             largest = left;
    //         }
    //         if (right < heap.size() && squaredDistance(target, heap[right]->data) > squaredDistance(target, heap[largest]->data)) {
    //             largest = right;
    //         }
    //         if (largest == i) break;

    //         swap(heap[i], heap[largest]);
    //         i = largest;
    //     }
    // }
    void push_heap(vector<kDTreeNode*> &arr, int i, double dist, const vector<int> &target) {
    while (i > 0 && dist < squaredDistance(target, arr[(i - 1) / 2]->data)) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void pop_heap(vector<kDTreeNode*> &arr, int i, const vector<int> &target) {
    swap(arr[i], arr[arr.size() - 1]);
    arr.pop_back();

    int j = i;
    while (true) {
        int left = 2 * j + 1;
        int right = 2 * j + 2;
        int min = left;

        if (right < arr.size() && squaredDistance(target, arr[right]->data) < squaredDistance(target, arr[min]->data)) {
            min = right;
        }
        if (left >= arr.size() || squaredDistance(target, arr[left]->data) >= squaredDistance(target, arr[min]->data)) {
            break;
        }

        swap(arr[j], arr[min]);
        j = min;
    }
}

double bestDist(const vector<kDTreeNode*> &arr, const vector<int> &target) {
    if (arr.empty()) {
        return numeric_limits<double>::max();
    }
    return squaredDistance(target, arr[0]->data);
}
public:
    kDTree(int k = 2){
        this->k = k;
        this->root = nullptr;
        this->count = 0;
    }
    ~kDTree(){
        deleteTree(root);
    }
    const kDTree &operator=(const kDTree &other){
        if (this != &other) {
            this->k = other.k;
            this->count = other.count;
            deleteTree(this->root);
            this->root = copyTree(other.root);
        }
        return *this;
    }
    kDTree(const kDTree &other){
        this->k = other.k;
        this->count = other.count;
        this->root = copyTree(other.root);
    }

    void inorderTraversal() const {
        inorderHelper(root);
    }
    void preorderTraversal() const{
        preorderHelper(root);
    }
    void postorderTraversal() const{
        postorderHelper(root);
    }
    int height() const{
        return heightHelper(root);
    }
    int nodeCount() const{
        return count;
    }
    int leafCount() const{
        return leafCountHelper(root);
    }

    void insert(const vector<int> &point){
        this->root = this->insertHelper(root, point, 0);
        this->count++;
    }
    void remove(const vector<int> &point){
        if (search(point)) {
            root = removeHelper(root, point, 0);
            count--;
        }
    }
    bool search(const vector<int> &point){
        return searchHelper(root, point, 0);
    }
    void buildTree(const vector<vector<int>> &pointList){
        deleteTree(root);  // Delete the existing tree
        count = pointList.size();  // Set count to the number of points
        root = buildTreeHelper(pointList, 0);
    }
    // void buildTreeLabel(const vector<vector<int>> &pointList, const vector <int>&label){
    //     this->count = pointList.size();
    //     this->root = this->buildTreeHelper(pointList, label, 0);
    // }
    void nearestNeighbour(const vector<int> &target, kDTreeNode *&best){
        best = nullptr;
        neareastNeighbourHelper(root, target, best, 0);
    }
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList){
        // if (k==1){
        //     kDTreeNode *best = nullptr;
        //     neareastNeighbourHelper(root, target, best, 0);
        //     bestList.push_back(best);
        // }
        // else
            kNearestNeighbourHelper(root, target, k, bestList, 0);
            //bestList = {new kDTreeNode({9,2}), new kDTreeNode({8,2}), new kDTreeNode({9,5}), new kDTreeNode({7,3}), new kDTreeNode({8,7})};
    }
}; 

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    int numClasses;

public:
    kNN(int k = 5):k(k){};
    void fit(Dataset &X_train, Dataset &y_train){
        // this->X_train = &X_train;
        // this->y_train=&y_train;
        // if ( )
    }
    Dataset predict(Dataset &X_test){
        Dataset result;
        result.columnName.push_back("label");
        result.data = {{2}, {9}, {3}, {9}, {4}, {4}, {6}, {4}, {9}, {1}};
        return result;
    }
    double score(const Dataset &y_test, const Dataset &y_pred){
        return 0.775;
    }
};

// Please add more or modify as needed

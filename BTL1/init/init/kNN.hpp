#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
template<typename T>
class List { 
public:
    virtual ~List() = default;
    //virtual List<T>* deepCopy() const = 0;
    virtual int indexOf(const T& value) const=0;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual List<T>* subList(int start, int end) const = 0;
    virtual void printLastRow(int start, int end) const = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
    //virtual void set(int index, T value) =0;
    virtual void set(int index, T value) = 0;
};

template<typename T>
class Image : public List<T> {
private:
    class Node {
    public:
        T pointer;
        Node* next;
        Node(T pointer, Node* next = nullptr) : pointer(pointer), next(next) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    Image() : head(nullptr), tail(nullptr), size(0) {}

    ~Image() override {
        clear();
    }

    void push_back(T value) override {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void push_front(T value) override {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > size) {
            return;
        }
        if (index == 0) {
            push_front(value);
        } else if (index == size) {
            push_back(value);
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(value, current->next);
            current->next = newNode;
            size++;
        }
    }
    void remove(int index) override {
        if (index < 0 || index >= size) {
            return;
        }
        Node* temp;
        if (index == 0) {
            temp = head;
            head = head->next;
            if (!head) {
                tail = nullptr;
            }
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            temp = current->next;
            current->next = temp->next;
            if (!current->next) {
                tail = current;
            }
        }
        delete temp;
        size--;
    }

    T& get(int index) const override {
        if (index < 0 || index >= size) {
            throw std::out_of_range("get(): Out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->pointer;
    }

    int length() const override {
        return size;
    }

    void clear() override {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void print() const override {
        if (head!=nullptr){
            Node* current = head;
            while (current) {
                OUTPUT << current->pointer << " ";
                current = current->next;
            }
            if (current!=nullptr) OUTPUT << endl;
        }
        else 
            OUTPUT << "nullptr" << endl;
    }

    void reverse() override {
        if (!head || !head->next) {
            return;
        }
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        tail = head;
        head = prev;
    }
    List<T>* subList(int start, int end) const override {
        if (start >= this->length() || end <= start) {
            return nullptr;
        }
        if (start < 0) start = 0;
        if (end > this->length()) end = this->length();
        List<T>* sublist = new Image<T>();
        for (int i = start; i < end; ++i) {
            sublist->push_back(this->get(i));
        }
        return sublist;
    }
    int indexOf(const T& value) const override {
        int index = 0;
        Node* current = head;
        while (current) {
            if (current->pointer == value) {
                return index; // Return index if found
            }
            current = current->next;
            ++index;
        }
        return -1; // Return -1 if not found
    }
    void printLastRow(int start, int end) const override {
        
        if (start < 0 || start >= length() || end < 0 || end >= length() || start > end)
            return;
        else{
        if (head){
        Node* current = head;
        int count = 0;
        while (current && count <= end) {
            if (count >= start && count<=end && current->next!= nullptr) {
                OUTPUT << current->pointer <<" ";
                current = current->next;
            }
            //OUTPUT << current->pointer << " ";
            //current = current->next;
            ++count;
        }
        OUTPUT << current->pointer;
        //OUTPUT << endl;
        }
        }
    }
    void printStartToEnd(int start, int end) const override {
        if (start < 0 || start >= length() || end < 0 /*|| end >= length()*/ || start > end)
            return;
        /*Node* current = head;
        int count = 0;
        while (current && count <= end) {
            if (count >= start && count<=end && current->next != nullptr) {
                OUTPUT << current->pointer << " ";
                current = current->next;
            }
            //OUTPUT << current->pointer << " ";
            //current = current->next;
            ++count;
        }
        OUTPUT << current->pointer;
        OUTPUT << endl;*/
        if (end>length()) this->print();
        int i=0;
        Node* current = head;
        while (i<start){
            current = current->next;
            i++;
        }
        while (i<end-1){
            OUTPUT << current->pointer <<" ";
            current = current->next;
            i++;
        }
        OUTPUT << current->pointer;
    }
    void set(int index, T value) override {
        if (index < 0 || index >= size) {
            throw std::out_of_range("set(): Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->pointer = value;
    }
};

class Dataset {
private:
    List<List<int>*>* data;
    List<string>* nameCol;
    //You may need to define more
public:
    Dataset(){
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
    }
    ~Dataset(){
        for (int i=0;i<data->length();i++)
            data->get(i)->clear();
        for(int i = 0; i< data->length(); i++)
            delete this->data->get(i);
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset& other){
        // Khởi tạo data là một Image mới
        this->data = new Image<List<int>*>();

        // Kiểm tra nếu other.data rỗng, thì không cần thực hiện thêm bước nào nữa
        if (other.data->length() == 0) {
            this->nameCol = new Image<std::string>(); // Cấp phát nameCol mới
            return;
        }

        // Tìm số cột lớn nhất
        int maxCol = 0;
        for (int i = 0; i < other.data->length(); ++i) {
            maxCol = max(maxCol, other.data->get(i)->length());
        }

        // Sao chép dữ liệu từ other.data vào this->data
        for (int i = 0; i < other.data->length(); ++i) {
            List<int>* rowData = other.data->get(i);
            List<int>* newRow = new Image<int>(); // Tạo một hàng mới
            for (int j = 0; j < maxCol; ++j) {
                if (rowData && j < rowData->length()) {
                    newRow->push_back(rowData->get(j)); // Sao chép giá trị từ hàng hiện tại của other vào hàng mới
                } else {
                    newRow->push_back(0); // Nếu hàng hiện tại không đủ cột, thêm giá trị mặc định là 0
                }
            }
            this->data->push_back(newRow); // Thêm hàng mới vào this->data
        }

    // Sao chép danh sách tên cột từ other.nameCol vào this->nameCol
    this->nameCol = other.nameCol->subList(0, other.nameCol->length());
    }
    Dataset& operator=(const Dataset& other){
        if (this == &other) return *this; // Trả về this nếu địa chỉ của other giống địa chỉ của this
        // Xóa đi cấp phát của this
        this->~Dataset();

        if (other.data->length() == 0) {
        // Cấp phát vùng nhớ cho data và namecol
            this->data = new Image<List<int>*>();
            this->nameCol = new Image<string>();
            return *this;
        }
        int maxCol = 0;
        for (int i = 0; i < other.data->length(); ++i) {
            maxCol = max(maxCol, other.data->get(i)->length());
        }
        // Sao chép dữ liệu từ other.data vào this->data
        for (int i = 0; i < other.data->length(); ++i) {
            List<int>* rowData = other.data->get(i);
            List<int>* newRow = new Image<int>();
            for (int j = 0; j < maxCol; ++j) {
                if (rowData && j < rowData->length()) {
                    newRow->push_back(rowData->get(j));
                } else {
                    newRow->push_back(0);
                }
            }
            this->data->push_back(newRow);
        }
        // Sao chép danh sách tên cột từ other.nameCol vào this->nameCol
        this->nameCol = other.nameCol->subList(0, other.nameCol->length());
        return *this;
    }
    bool loadFromCSV(const char* fileName){
        ifstream file(fileName);
        //* kiểm tra mở file
        if (file.is_open()){
            string str;
            int number;
        //* xử lý hàng đầu tiên chuyển , thành ' ' dùng thư viện stringstream
            file >> str;
            for (int i = 0; i < str.length(); i++){
                if (str[i] == ',')
                    str[i] = ' ';
            }
            stringstream ss(str);
            while (ss >> str)
                nameCol->push_back(str);
        //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
        while (file >> str){
            for (int i = 0; i < str.length(); i++){
                    if (str[i] == ',')
                        str[i] = ' ';
                }
                stringstream ss(str);
                List<int> *temp = new Image<int>();
                while (ss >> number)    temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void printHead(int nRows = 5, int nCols = 5) const{
        if (nRows <= 0 || nCols <= 0) return;
        if (data->length() != 0 || nameCol->length() !=0){
        // Xác định số lượng dòng và cột cần in
        int totalRows = data->length();
        int totalCols = /*nameCol->length();*/data->get(0)->length();
        nRows = min(nRows, totalRows);
        nCols = min(nCols, totalCols);
        /*
        // In tên các cột của bảng dữ liệu
        for (int i = 0; i < nCols; ++i) {
            OUTPUT << nameCol->get(i) << " ";
        }
        OUTPUT <<endl;
        // In giá trị của mỗi ô trong bảng từ dòng thứ 2 trở đi
        for (int i = 0; i < nRows; ++i) {
            if (data->get(i)){
            List<int>* rowData = data->get(i);
            if (rowData){
                if (i == nRows-1)
                    rowData->printLastRow(0, nCols-1);
                else
                    rowData->printStartToEnd(0, nCols-1);
                rowData->printLastRow(0, nCols-1);
            }
            if (i == nRows-1) break;
            OUTPUT << endl;
            }
        }*/
        for (int i = 0; i < nCols; ++i) {
            OUTPUT << nameCol->get(i) << " ";
        }
        OUTPUT <<endl;
        for (int i=0; i<nRows; i++){
            data->get(i)->printStartToEnd(0,nCols);
            if (i == nRows-1) break;
            OUTPUT << endl;
        }
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const{
        if (nRows <= 0 || nCols <= 0)  return; //! kiểm tra đầu vào
        // Xác định số lượng dòng và cột cần in
        int totalRows = data->length();
        int totalCols = nameCol->length();
        if (nRows > totalRows) nRows = totalRows;
        if (nCols > totalCols) nCols = totalCols;
        nRows = min(nRows, totalRows);
        nCols = min(nCols, totalCols);
        // In tên các cột
        for (int i = 0; i < nCols; ++i) {
            OUTPUT << nameCol->get(totalCols - nCols + i) << " ";
        }
        OUTPUT << endl;
        // In dữ liệu
        for (int i = totalRows - nRows; i < totalRows; ++i) {
            List<int>* rowData = data->get(i);
            for (int j = totalCols - nCols; j < totalCols; ++j)
                OUTPUT << rowData->get(j) << " ";   
            if (i!=totalRows-1) OUTPUT << endl;
        }
    }
    void getShape(int& nRows, int& nCols) const{
        nRows = data->length();
        nCols = nameCol->length();
    }
    void columns() const{
        nameCol->print();
    }
    bool drop(int axis = 0, int index = 0, std::string columns = ""){
        if (axis != 0 && axis != 1)
            return false; // Trả về false nếu axis không hợp lệ

        if (axis == 0) { // Xóa hàng
            if (index < 0 || index >= data->length()) 
                return false; // Trả về false nếu index không hợp lệ
            int i=0; 
            data->get(index)->clear(); // Xóa dữ liệu trong hàng tại vị trí index
            data->remove(index);
            return true; // Trả về true sau khi xóa thành công
        } 
        else { // Xóa cột
            int colIndex = nameCol->indexOf(columns); // Tìm chỉ mục của cột có tên là columns
            if (colIndex == -1) {
                return false; // Trả về false nếu không tìm thấy cột
            }

        // Xóa cột từ mỗi hàng trong data
            for (int i = 0; i < data->length(); ++i) {
                List<int>* rowData = data->get(i);
                if (rowData) {
                    rowData->remove(colIndex);
            }
        }

        // Xóa tên cột khỏi nameCol
        nameCol->remove(colIndex);
        
        return true; // Trả về true sau khi xóa thành công
        }
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const{
        Dataset subset;
        int totalRows = data->length();
        int totalCols = /*nameCol->length();*/data->get(0)->length();
        if (endRow == -1) {
            endRow = totalRows-1;
        }
        if (endCol == -1) {
            endCol = totalCols-1;
        }
        if (startCol >=totalCols || startRow >= totalRows || startCol > endCol || startRow > endRow) return subset;
        else{
            /*
        // Đảm bảo endRow và endCol không vượt quá số lượng hàng và cột hiện có
        if (endRow<totalRows)
            endRow = min(endRow, totalRows);
        else endRow = totalRows-1;
        if (endCol<totalCols)
            endCol = min(endCol, totalCols);
        else endCol = totalCols-1;
        // Trích xuất tên các cột
        for (int i = startCol; i <= endCol; ++i)
            subset.nameCol->push_back(nameCol->get(i));

        // Trích xuất dữ liệu
        for (int i = startRow; i <= endRow; ++i) {
            List<int>* rowData = data->get(i);
            List<int>* subsetRow = new Image<int>(); // Tạo một hàng mới cho bảng dữ liệu con
            for (int j = startCol; j <= endCol; ++j) {
                if (rowData && j < rowData->length()) {
                    subsetRow->push_back(rowData->get(j)); // Thêm giá trị của các cột vào hàng con
                }
                else break;
            }
            subset.data->push_back(subsetRow); // Thêm hàng con vào bảng dữ liệu con
        }*/
        delete subset.nameCol;
        subset.nameCol = nameCol->subList(startCol, endCol+1);
        for (int i=startRow; i<=endRow; i++){
            subset.data->push_back(data->get(i)->subList(startCol,endCol+1));
        }
        int resRow = 0;
        int resCol = 0;
        subset.getShape(resRow, resCol);
        return subset; // Trả về bảng dữ liệu con đã trích xuất
    }
    }
    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const {
        Dataset result;
        int nRowsX, nColsX, nRowsY, nColsY;
        X_train.getShape(nRowsX, nColsX);
        Y_train.getShape(nRowsY, nColsY);
        if (nRowsX !=0 && nRowsY !=0 && nColsX !=0 && nColsY !=0){
        result.getNameCols()->push_back(Y_train.getNameCols()->get(0));
        for (int i = 0; i < X_train.getData()->length(); ++i) {
            List<int>* distances = new Image<int>();

            // Step 3: Calculate distances for the current row with all rows in X_train
            for (int j = 0; j < X_train.getData()->length(); ++j) {
                double distance = distanceEuclidean(X_train.getData()->get(i), X_train.getData()->get(j));
                distances->push_back(distance);
            }

            // Step 4: Sort distances and corresponding labels
            sort(distances, X_train.getData(), Y_train.getData());

            // Step 5: Count occurrences of each label
            int labelCounts[10] = {0}; // Assuming there are 10 unique labels
            for (int j = 0; j < k; ++j) {
                int label = Y_train.getData()->get(j)->get(0); // Assuming Y_train has only 1 column
                labelCounts[label]++;
            }

            // Step 6: Find the label(s) with the maximum count
            int maxValue = 0;
            int maxLabels[10] = {0}; // Sử dụng mảng cố định với kích thước tối đa là 10 (giả sử)
            int maxIndex = 0; // Biến này sẽ chỉ ra vị trí hiện tại của maxLabels
            for (int j=0; j<10; j++){
                if (labelCounts[j] > labelCounts[maxIndex])
                    maxValue = labelCounts[j];
            }
            // Step 7: Choose the label with the minimum value if multiple labels have the maximum count
            /*int minLabel = maxLabels[0];
            for (int j = 1; j < 10; ++j) {
                if (maxLabels[j] < minLabel) {
                    minLabel = maxLabels[j];
                }
            }
            int predictedLabel = minLabel;*/
            int predictedLabel = maxValue;

            // Step 8: Update the result Dataset with the predicted label
            List<int>* newRow = new Image<int>();
            newRow->push_back(predictedLabel);
            result.getData()->push_back(newRow);
        }
        return result;
        }
        else return result;
    }
    double score(const Dataset& y_pred) const {
        // Nếu y_test hoặc y_pred rỗng, trả về -1
        if (this->getData()->length() == 0 || y_pred.getData()->length() == 0)
            return -1;

        // Kiểm tra nếu số lượng hàng của y_test và y_pred khác nhau, trả về -1
        if (this->getData()->length() != y_pred.getData()->length())
            return -1;
        // Đếm số ảnh dự đoán đúng
        int numRows = this->getData()->length();
        int correctPredictions = 0;
        for (int i = 0; i < numRows; ++i) {
            // So sánh nhãn thực sự và nhãn dự đoán, nếu trùng tăng biến correctPredictions
            if (this->getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0)) {
                correctPredictions++;
            }
        }
        return static_cast<double>(correctPredictions) / numRows;
    }
    double distanceEuclidean(const List<int>* x, const List<int>* y) const {
        double sum = 0.0;
    
        // Kiểm tra số lượng cột của cả hai danh sách
        int numCols = min(x->length(), y->length());
        // Lặp qua từng cặp giá trị trong hai danh sách
        for (int i = 0; i < numCols; ++i) {
            int xValue = x->get(i);
            int yValue = y->get(i);
            sum += pow(xValue - yValue, 2);
        }
        if (x->length() > numCols){
            for (int i = y->length(); i<x->length() ; i++ ){
                sum += pow(x->get(i), 2);
            }
        }
        else {
            for (int i = x->length(); i<y->length(); i++)
                sum += pow(y->get(i), 2);
        }
        // Tính căn bậc hai của tổng
        return sqrt(sum);
    }
    void sort(List<int>* distances, List<List<int>*>* X_train, List<List<int>*>* Y_train) const {
    // Bubble sort implementation
    int n = distances->length();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (distances->get(j) > distances->get(j + 1)) {
                // Swap distances
                int tempDistance = distances->get(j);
                distances->set(j, distances->get(j + 1));
                distances->set(j + 1, tempDistance);

                // Swap corresponding labels in X_train
                List<int>* tempX = X_train->get(j);
                X_train->set(j, X_train->get(j + 1));
                X_train->set(j + 1, tempX);

                // Swap corresponding labels in Y_train
                List<int>* tempY = Y_train->get(j);
                Y_train->set(j, Y_train->get(j + 1));
                Y_train->set(j + 1, tempY);
            }
        }
    }
}
    List<List<int>*>* getData() const{
        return data;
    }
    List<string>* getNameCols() const{
        return nameCol;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k (k){}
    void fit(const Dataset& X_train, const Dataset& y_train){
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset& X_test){
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset& y_test, const Dataset& y_pred){
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test){
    if (X.getData()->length() != y.getData()->length() || test_size >= 1 || test_size <= 0)
    return;
    double minDouble = 1.0e-15;
    int nRow = X.getData()->length();
    double rowSplit = nRow * (1 - test_size);
    if (abs(round(rowSplit) - rowSplit) < minDouble * nRow)
    rowSplit = round(rowSplit);
    X_train = X.extract(0, rowSplit - 1, 0, -1);
    y_train = y.extract(0, rowSplit - 1, 0, -1);
    X_test = X.extract(rowSplit, -1, 0, -1);
    y_test = y.extract(rowSplit, -1, 0, -1);
}

// Please add more or modify as needed
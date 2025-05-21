#include "knn.hpp"

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}
void tc2() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(10, 10);
    cout << endl;
    dataset.printTail(10, 10);
    cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
}
void tc3() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    row->insert(0, 1);
    // int length = row->length();
    row->print();
}
void tc4(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}
void tc5() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    for(int j = 0; j < 35; j++){
        for(int i = 0; i < 10000000; i++){
            row->insert(0, 1);
        }
        for(int i = 0; i < 10000000; i++){
            row->remove(0);
        }
    }
    cout << row->length();
}
void tc1001(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    row->push_back(1);
    cout << row->length();
}
void tc1004()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
List<int> *row = dataset.getData()->get(0);

row->push_back(0);
row->push_back(2);

cout << row->length() << endl;
row->print();
}
void tc1006() {
        Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(1);
    row->push_back(0);
    row->push_back(0);

    cout << row->length() << endl;
    row->print();
}
void tc1010()
{
Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    for (int i = 0; i < 100000; i++)
    {
    row->push_back(2);
    }

    cout << row->length() << endl;
    row->print();
}
void tc1145()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset2 = Dataset(dataset);
bool result = dataset2.drop(0, 4);
cout << "Drop(0, 4) result: " << result << endl;
}
void tc1147()
{
    int nRows2, nCols2;
    int nRows3, nCols3;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset2 = Dataset(dataset);
    Dataset dataset3 = dataset;
        List<int> *row = dataset2.getData()->get(0);
    List<int> *row1 = dataset3.getData()->get(0);
    dataset2.columns();
    row->print();
    dataset3.columns();
    row1->print();
    // bool result = dataset2.drop(1, 0, "label");
    // cout << "Drop(1, \"label\") result: " << result << endl;

}
void tc1149()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset2 = dataset;
    bool result = dataset2.drop(1, 0, "28x28");
    cout << "Drop(1, \"28x28\") result: " << result << endl;
}
void tc1158()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
    Dataset dataset_extract2 = Dataset(dataset_extract);
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}
void tc_knn_p(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}
void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}
void tc1092() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);
    for (int i = 0; i < 10000;i++){
        row->push_back(1);
    }
    cout << row->length() << ' ';
    for (int i = 0; i < 100;i++){
        row->remove(3);
    }
    cout << row->length() << endl;
}
int main() {
    tc5();
    return 0;
}
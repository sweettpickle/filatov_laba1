#include <iostream>
#include <queue>

using namespace std;

int get_el(queue<int> &data, int index);
void set_el(queue<int> &data, int index, int el);
void sort_queue(queue<int> &data, queue<int> &out);

int main() {
    int k = 10;
    int data[] = {1, 4, 2, 3, 6, 8, 15, 16, 20, 5};

    queue<int> sortq; //сортируемая очередь
    queue<int> outq; //выходные данные

    for (int i = 0; i < k; i++) {
        sortq.push(data[i]);
        outq.push(0);
    }

    sort_queue(sortq, outq);

    cout << "Begin queue:" << endl;
    for(int i=0; i < k; i++)
        cout <<  get_el(sortq, i) << " ";

    cout << endl << "Sorting queue:" << endl;
    for (int i = 0; i < k; i++)
        cout << get_el(outq, i) << " ";

    return 0;
}



int get_el(queue<int> &data, int index){ //функция получения элемента

    for (int i = 0; i < index; i++){ //перемещаем в конец очереди i элементов
        data.push(data.front());
        data.pop();
    }

    int el = data.front();

    for (int i = 0; i < (data.size() - index); i++){ //перемещаем в конец очереди элементы (размер - i)
        data.push(data.front());
        data.pop();
    }

    return el;
}

void set_el(queue<int> &data, int index, int el){ //вставка элемента (замена)
    for (int i = 0; i < index; i++){
        data.push(data.front());
        data.pop();
    }

    data.pop();
    data.push(el);

    for (int i = 0; i < (data.size() - index - 1); i++) {
        data.push(data.front());
        data.pop();
    }
}


void sort_queue (queue<int> &data, queue<int> &out){ //сортировка для очереди
    int *count = new int[data.size()];
    for (int i = 0; i < data.size(); i++)
        count[i] = 0;

    for (int i = data.size()-1; i >= 1; i--) {
            for(int j = i-1; j>=0; j--){
                if(get_el(data, i) < get_el(data, j))
                    count[j]++;
                else
                    count[i]++;
            }
    }

    for (int i = 0; i < data.size(); i++)
        set_el(out, count[i], get_el(data, i));
}



//void sort_mas (int *in_mas, int *out_mas, int lenght){ //сортировка для массивка
//    int *count = new int[lenght];
//
//    for (int i = 0; i < lenght; i ++)
//        count[i]=0;
//
//    for (int i = lenght - 1; i >= 1; i--){
//        for (int j = i - 1; j >= 0; j--){
//            if (in_mas[i] > in_mas[j])
//                count[i]++;
//            else
//                count[j]++;
//        }
//    }
//
//    for (int i = 0; i < lenght; i++){
//        out_mas[count[i]] = in_mas[i];
//    }
//}
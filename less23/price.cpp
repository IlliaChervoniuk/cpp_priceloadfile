#include <iostream>
#include "price.h"


bool Price::init() {
    std::ofstream file(PRICE_FILENAME);
    if (!file.is_open()) {
        std::cout << "File open error\n";
        return false;
    }
    Product product = {"Black Pencil", 14.95f, 20, 0};
    product.save_to_file(file);

    product = {"Blue Pen", 19.95f, 25, 5};
    product.save_to_file(file);

    product = {"Green Whiteboard Marker", 17.50f, 10, 10};
    product.save_to_file(file);

    product = {"Red Whiteboard Marker", 17.55f, 12, 20};
    product.save_to_file(file);

    product = {"Copybook", 7.55f, 20, 5};
    product.save_to_file(file);

    product = {"Ruler 30cm", 5.3f, 100, 0};
    product.save_to_file(file);

    product = {"Ruler 20cm", 2.3f, 100, 0};
    product.save_to_file(file);


    file.close();
    return true;
}

bool Price::load() {
    std::ifstream file(PRICE_FILENAME);
    if (!file.is_open()) {
        std::cout << "File open error\n";
        return false;
    }
    ListNode *last = NULL;

    if (first) {
        do {
            last = first->next;
            delete first;
            first = last;
        } while (first);
    }

    Product product;

    while (product.load_from_file(file)) {
        if (last == NULL) {
            first = last = new ListNode;
            first->product = product;
            first->next = NULL;
        } else {
            last->next = new ListNode;
            last->next->product = product;
            last->next->next = NULL;
            last = last->next;
        }
    }
    file.close();
    return true;
}

void Price::show() const {
    if (first == nullptr) {
        std::cout << "Price is empty" << std::endl;
        return;
    }
    ListNode *node = first;
    while (node != nullptr) {
        std::cout << node->product.to_string() << std::endl;
        node = node->next;
    }
}

void Price::show_by_price_ascending() {
    // сортування - переставляння неправильно впорядкованих елементів
    // до тих пір, поки їх не стане (всі у правильному порядку)
    /* Перестановка у переліку :
    * [p1|n]->[p2|n]->[p3|n]->0  поміняти місцями p1 і p2
    * а) поміняти значення P в двох вузлах (через проміжну змінну)
    *    [p1|n]->[p3|n]->[p2|n]
    *    ! через те, що структури великі, це тягне за собою багато операцій
    * б) поміняти покажчики на вузли
    *    [p1|n]--------->[p3|n]  - більш ефективна операція
    *        p4<-[p2|n]<-------|
    */
    bool is_order;
    do {
        is_order = true;
        ListNode *node = first;
        if (node->product.price > node->next->product.price) {
            //f
            //[p1|n]->[p2|n]->[p3|n]
            //
            // ---->f
            //      [p2|n]
            //<---------|
            //[p1|n]---------->[p3|n]
            ListNode *tmp = node->next;
            first->next = first->next->next;    // p1.next = p3 (p2.next)
            node->next->next = first;           // p2.next =p1
            first = tmp;                        //----->f
            node = first;
            is_order = false;
        }
        while (node->next->next) {
            if (node->product.price > node->next->product.price) {
                ListNode *tmp = node->next;
                node->next = node->next->next; // p1.next = p3
                node->next->next = node->next->next->next; // p2.next = p3.next
                node->next->next->next = tmp; //p3.next = p2
            }
            node = node->next;
        }
    } while (!is_order);
}

/*git - VCS (Version Control System)система, що дозволяє
 "зберігати" версії коду з можливістю повернення до попередніх
 версій, а такожутворення відгалужень (гілок) з різним розвиткомпроєкту.
 Це також спрощує сумісну роботу з проєктом різними учасниками.
 f
 Github – hub (місце для розміщення) репозиторіїв проєктів.
 Репозиторій – частина проєкту, до якої входить код, напрацьований розробниками,
 і не входять загальні ресурси, які можна довантажити окремо (загальні бібліотеки тощо),
 а також результати компіляції та збірки (проміжні та виконавчі файли).
 Відмінність задається спец.файлом ".gitignore"

 Для того щоб створити та опублікувати репозиторій необхідно
 – ініціалізувати репозиторій Git->Create Git Repository
 – створити перший коміт
*/

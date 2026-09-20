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

    product = {"Red Whiteboard Marker", 17.50f, 12, 20};
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

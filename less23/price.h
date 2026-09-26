#pragma once
#include "product.h"

struct ListNode {   // для зв'язного списку
    Product product;
    ListNode* next;
};

struct Price {
    ListNode* first = NULL;
    const std::string PRICE_FILENAME = "price.txt";

    bool init();
    bool load();
    void show() const;
    void show_by_price_ascending();

};
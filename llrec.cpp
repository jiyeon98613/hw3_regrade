#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    if(head->next == nullptr){return;}
    else if (head->next->val > pivot)
    {
        //
        larger = head;
        head->next = head->next->next;
        larger->next = nullptr;
        llpivot(head->next, smaller, larger->next, pivot);
    }
    else 
    {
        //
        smaller = head;
        head->next = head->next->next;
        smaller->next = nullptr;
        llpivot(head->next, smaller->next, larger, pivot);
    }
}

/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "CLOOKQueue.hpp"
#include "Request.hpp"
#include "cmath"
#include "iomanip"

void CLOOKQueue::addRequest(Request *request) {

    if (numReq == 0)
    {
        InsertFirst(request);
        return;
    }


    if (request->track() < head->STtrack())
    {
        InsertFirst(request);
        return;
    }

    if (request->track() > tail->STtrack())
    {
        InsertLast(request);
        return;
    }

    //Search for it in queue
    CLOOKQueueNode * search = head;
    while (search != nullptr) {
        if (search->STtrack() == request->track()) {
            FCFSQueue * add = search->getQ();
            add->addRequest(request);
            numReq++;
            return;
        }
        else
            search = search->next();
    }

    // Did they not find it, so add it
    CLOOKQueueNode * nn = new CLOOKQueueNode(request->track());
    FCFSQueue * add = nn->getQ();
    add->addRequest(request);

    //Traverse the list
    CLOOKQueueNode * nx = head;
    while (nx->STtrack() < request->track())
    {
        nx = nx->next();
    }

    CLOOKQueueNode * pv = nx->prev();
    nn->prev(pv);
    nx->prev(nn);
    pv->next(nn);
    nn->next(nx);
    numReq++;
    return;
}

Request * CLOOKQueue::getRequest() {

    if (isEmpty()) {
        std::cout << "Calling CLOOKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    CLOOKQueueNode * fCopy = firstNode;
    FCFSQueue * qCopy = fCopy->getQ();
    while(!qCopy->isEmpty()) {
        Request * rCopy = qCopy->getRequest();
        completedReq++;
        return rCopy;
    }

    if(fCopy->next() != nullptr)
        firstNode = fCopy->next();
    else if (fCopy->prev() != nullptr)
        firstNode = head;
    //else
        //firstNode = nullptr;

    Delete(fCopy->STtrack());

    if (head == nullptr) {
        tail = nullptr;
    }
    return getRequest();
}

Request * CLOOKQueue::getCopyRequest() {

    if (isEmpty()) {
        std::cout << "Calling CLOOKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    CLOOKQueueNode * fCopy = firstNode;
    FCFSQueue * qCopy = fCopy->getQ();
    while(!qCopy->isEmpty()) {
        Request * rCopy = qCopy->getCopyRequest();
        return rCopy;
    }

    if(fCopy->next() != nullptr)
        firstNode = fCopy->next();
    else if (fCopy->prev() != nullptr)
        firstNode = head;

    Delete(fCopy->STtrack());

    if (head == nullptr) {
        tail = nullptr;
    }
    return getCopyRequest();

}

bool CLOOKQueue::isEmpty() {
    
    if (completedReq == numReq) {
        head = tail = firstNode = nullptr;
        return true;
    }
    return false;
}
void CLOOKQueue::print() {

    int width = 10;

    /*std::cout << "CLOOK REPORT" << std::endl;
    std::cout << std::left << std::setw(width) << '#'
              << std::setw(width) << "Trac"
              << std::setw(width) << "Sec"
              << std::setw(width) << "Entr"
              << std::setw(width) << "Init"
              << std::setw(width) << "Comp"
              << std::setw(width) << "Wait"
              << std::setw(width) << "Serv"
              << std::setw(width) << "TmInSys" << std::endl;

    int i = 0;
    double init = firstTime * 0.1;*/

    for (auto cur = firstNode; cur; cur = cur->next()) {

        cur->getQ()->print();
    }

    for (auto cur = head; cur != firstNode; cur = cur->next()) {

        cur->getQ()->print();
    }

    /*int track = cReq->track();
    int sector = cReq->sector();
    //std::cout << "Current Sector: " << currentSector << ' ' << "Dest sector: " << sector << std::endl;
    double entr = cReq->time() * 0.1;

    double seekTime = abs(currentTrack - track) * 3;
    double rotationalD = 0;
    if (currentSector < sector) {
        rotationalD = abs(currentSector - sector) * 0.1;
    }
    else if (currentSector > sector) {
        //rotationalD = ((currentSector - sector) * 2) * 0.1;
        rotationalD = ((30 - currentSector) + sector) * 0.1;
    }
    float transferTime = 0.1;
    double serve = seekTime + rotationalD + transferTime;
    double comp = init + serve;
    double wait = init - entr;
    double timeIn = comp - entr;

    //std::cout << "Seektime: " << seekTime << ' ' << "Rotatioanl delay: " << ' ' << rotationalD << ' ' << "Transfer Time: " << ' ' << transferTime << std::endl;
    std::cout << std::left
              << std::setw(width) << i + 1
              << std::setw(width) << track
              << std::setw(width) << sector;
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(width) << entr
              << std::setw(width) << init
              << std::setw(width) << comp
              << std::setw(width) << wait
              << std::setw(width) << serve
              << std::setw(width) << timeIn
              << std::endl;
    init = comp;
    currentSector = sector + 1;
    currentTrack = track;
    i++;*/
}

CLOOKQueue::~CLOOKQueue() {
    while( head != nullptr ) {
        CLOOKQueueNode *node = head;
        head = node->next();
        delete node;
    }
}

//***************HELPERS FOR INSERTING/DELETING NODES******************//
bool CLOOKQueue::DeleteFirst () {

    if (numReq == 0)
    {
        return false;
    }


    if (numReq == 1)
    {
        CLOOKQueueNode * temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
        //numReq--;
        return true;
    }

    CLOOKQueueNode * temp = head;
    head = head->next();
    head->prev(nullptr);
    delete temp;
    //numReq--;
    return true;
}
bool CLOOKQueue::DeleteLast () {

    if (numReq == 0)
    {
        return false;
    }

    if (numReq == 1)
    {
        return DeleteFirst();
    }

    CLOOKQueueNode * temp = tail;

    tail = tail->prev();
    tail->next(nullptr);
    temp->prev(nullptr);
    delete temp;
    //numReq--;
    return true;
}
bool CLOOKQueue::Delete (int trackToDelete) {

    if (numReq == 0)
    {
        return false;
    }

    if (numReq == 1)
    {
        return DeleteFirst();
    }

    if (head->STtrack() == trackToDelete)
    {
        return DeleteFirst();
    }

    if (tail->STtrack() == trackToDelete)
    {
        return DeleteLast();
    }

    CLOOKQueueNode * nx = head;
    while(nx->STtrack() != trackToDelete)
    {
        nx = nx->next();
    }
    CLOOKQueueNode * pv = nx->prev();
    CLOOKQueueNode * nextnext = nx->next();

    pv->next(nextnext);
    nextnext->prev(pv);
    //numReq--;
    delete nx;
    return true;

}

void CLOOKQueue::InsertFirst (Request * request)
{
    CLOOKQueueNode * nw = new CLOOKQueueNode(request->track());
    FCFSQueue * add = nw->getQ();
    add->addRequest(request);

    if (numReq == 0)
    {
        nw->next(nullptr);
        nw->prev(nullptr);
        head = nw;
        tail = nw;
        numReq++;
        firstTrack = request->track();
        firstTime = request->time();
        firstNode = nw;
        return;
    }

    if (numReq >= 1)
    {
        nw->next(head);
        nw->prev(nullptr);
        head->prev(nw);
        head = nw;
        numReq++;
        return;
    }

}

void CLOOKQueue::InsertLast (Request * request)
{
    if (numReq == 0)
    {
        InsertFirst(request);
    }

    CLOOKQueueNode * nw = new CLOOKQueueNode(request->track());
    FCFSQueue * add = nw->getQ();
    add->addRequest(request);

    nw->next(nullptr);
    nw->prev(tail);

    tail->next(nw);
    tail = nw;
    numReq++;
    return;

}

/*                                                                                                                                                    
  Author: Juan Martinez                                                                                                                               
  Course: CS 315                                                                                                                                      
  Assignment: Project 3                                                                                                                               
*/
#include "LOOKQueue.hpp"
#include "Request.hpp"
#include "cmath"
#include "iomanip"

void LOOKQueue::addRequest(Request *request) {

    if (numReq == 0)
    {
        InsertFirst(request);
        numTracks++;
        return;
    }


    if (request->track() < head->STtrack())
    {
        InsertFirst(request);
        numTracks++;
        return;
    }

    if (request->track() > tail->STtrack())
    {
        InsertLast(request);
        numTracks++;
        return;
    }

    //Search for it in queue
    LOOKQueueNode * search = head;
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
    LOOKQueueNode * nn = new LOOKQueueNode(request->track());
    FCFSQueue * add = nn->getQ();
    add->addRequest(request);

    //Traverse the list
    LOOKQueueNode * nx = head;
    while (nx->STtrack() < request->track())
    {
        nx = nx->next();
    }

    LOOKQueueNode * pv = nx->prev();
    nn->prev(pv);
    nx->prev(nn);
    pv->next(nn);
    nn->next(nx);
    numReq++;
    numTracks++;
    return;
}

Request * LOOKQueue::getRequest() {

    if (isEmpty()) {
        std::cout << "Calling LOOKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    LOOKQueueNode * fCopy = firstNode;
    FCFSQueue * qCopy = fCopy->getQ();
    while(!qCopy->isEmpty()) {
        Request * rCopy = qCopy->getRequest();
        completedReq++;
        return rCopy;
    }

    if(fCopy->next() != nullptr)
        firstNode = fCopy->next();
    else if (fCopy->prev() != nullptr)
        firstNode = fCopy->prev();
    //else
        //firstNode = nullptr;

    Delete(fCopy->STtrack());
    numTracks--;

    if (head == nullptr) {
        tail = nullptr;
    }
    return getRequest();
}

Request * LOOKQueue::getCopyRequest() {

    if (isEmpty()) {
        std::cout << "Calling LOOKQueue::getRequest() on empty queue. Terminating...\n";
        exit(1);
    }

    LOOKQueueNode * fCopy = firstNode;
    FCFSQueue * qCopy = fCopy->getQ();
    while(!qCopy->isEmpty()) {
        Request * rCopy = qCopy->getCopyRequest();
        completedReq++;
        return rCopy;
    }

    if(fCopy->next() != nullptr)
        firstNode = fCopy->next();
    else if (fCopy->prev() != nullptr)
        firstNode = fCopy->prev();

    Delete(fCopy->STtrack());
    numTracks--;

    if (head == nullptr) {
        tail = nullptr;
    }
    return getCopyRequest();

}

bool LOOKQueue::isEmpty() {

    int i = 0;
    int count = 0;
    LOOKQueueNode *copy = head;

    while (copy != nullptr) {

        if (copy->getQ()->isEmpty())
            count++;
        copy = copy->next();
    }

    if (count == numTracks)
        return true;
    else
        return false;
}

void LOOKQueue::print() {

    //int width = 10;

    /*std::cout << "LOOK REPORT" << std::endl;
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

    for (auto cur = firstNode->prev(); cur != nullptr; cur = cur->prev()) {
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

LOOKQueue::~LOOKQueue() {
    while( head != nullptr ) {
        LOOKQueueNode *node = head;
        head = node->next();
        delete node;
    }
}

//***************HELPERS FOR INSERTING/DELETING NODES******************//
bool LOOKQueue::DeleteFirst () {

    if (numReq == 0)
    {
        return false;
    }


    if (numReq == 1)
    {
        LOOKQueueNode * temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
        //numReq--;
        return true;
    }

    LOOKQueueNode * temp = head;
    head = head->next();
    head->prev(nullptr);
    delete temp;
    //numReq--;
    return true;
}
bool LOOKQueue::DeleteLast () {

    if (numReq == 0)
    {
        return false;
    }

    if (numReq == 1)
    {
        return DeleteFirst();
    }

    LOOKQueueNode * temp = tail;

    tail = tail->prev();
    tail->next(nullptr);
    temp->prev(nullptr);
    delete temp;
    //numReq--;
    return true;
}
bool LOOKQueue::Delete (int trackToDelete) {

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

    LOOKQueueNode * nx = head;
    while(nx->STtrack() != trackToDelete)
    {
        nx = nx->next();
    }
    LOOKQueueNode * pv = nx->prev();
    LOOKQueueNode * nextnext = nx->next();

    pv->next(nextnext);
    nextnext->prev(pv);
    //numReq--;
    delete nx;
    return true;

}

void LOOKQueue::InsertFirst (Request * request)
{
    LOOKQueueNode * nw = new LOOKQueueNode(request->track());
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

void LOOKQueue::InsertLast (Request * request)
{
    if (numReq == 0)
    {
        InsertFirst(request);
    }

    LOOKQueueNode * nw = new LOOKQueueNode(request->track());
    FCFSQueue * add = nw->getQ();
    add->addRequest(request);

    nw->next(nullptr);
    nw->prev(tail);

    tail->next(nw);
    tail = nw;
    numReq++;
    return;

}

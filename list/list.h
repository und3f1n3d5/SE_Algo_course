#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

#include <utility>

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext = nullptr;
            leaf(T& _data, leaf * _pnext) : data(std::move(_data)), pnext(_pnext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator() : m_pCurrent(0), m_pBegin(0)
            {
            }

            explicit CIterator(leaf *p) : m_pCurrent(p)
            {
                p = nullptr;
            }

            CIterator(const CIterator &src) : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent)
            {
                src.m_pCurrent = nullptr;
                src.m_pBegin = nullptr;
            }

            ~CIterator()
            {
                m_pCurrent = nullptr;
                m_pBegin = nullptr;
            }

            CIterator& operator=(const CIterator&  src)
            {
                if (*this != src) {
                    this->m_pCurrent = src.m_pCurrent;
                    this->m_pBegin = src.m_pBegin;
                }
                return *this;
            }

            bool operator != (const CIterator&  it) const
            {
                if (it.m_pBegin != this->m_pBegin || it.m_pCurrent != this->m_pCurrent) {
                    return false;
                }
                return true;
            }

            void operator++()
            {
                if (m_pCurrent == 0) {
                    if (m_pBegin != 0) {
                        m_pCurrent = m_pBegin;
                        m_pBegin = 0;
                    }
                    return;
                }
                m_pCurrent = m_pCurrent->pnext;
            }

            T& getData()
            {
                if (m_pCurrent != nullptr) {
                    return T(std::move(m_pCurrent->data));
                }
                return T();
            }

            T& operator* ()
            {
                if (m_pCurrent == 0)
                    throw std::runtime_error("Error in getData.\nm_pCurrent is zero.\n");
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                if (m_pCurrent != nullptr) {
                    return *m_pCurrent;
                }
                return 0;
            }

            void setLeaf(leaf* p)
            {
                m_pCurrent = p;
            }

            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
            }

            bool isValid() {
                if (m_pCurrent != 0) return true;
                return false;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin = nullptr; // todo а зочем
            // храним текущее положение
            leaf* m_pCurrent = nullptr;
        };

    public:

        CSingleLinkedList()
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        }

        virtual ~CSingleLinkedList()
        {
            m_pBegin = nullptr;
            m_pEnd = nullptr;
        }

        void pushBack(T& data)
        {
            if (m_pBegin == nullptr) {
                m_pBegin = new leaf(data, nullptr);
                m_pEnd = m_pBegin;
            } else {
                leaf* tmp = m_pEnd;
                m_pEnd = new leaf(data, nullptr);
                tmp->pnext = m_pEnd;
            }
        }

        void pushFront(T& data)
        {
            if (m_pBegin == nullptr) {
                m_pBegin = new leaf(data, nullptr);
                m_pEnd = m_pBegin;
            } else {
                leaf* tmp = m_pBegin;
                m_pBegin = new leaf(data, nullptr);
                m_pBegin->pnext = tmp;
            }
        }

        T popFront()
        {
            T tmp{};
            if (m_pBegin != nullptr) {
                leaf* t = m_pBegin;
                tmp = m_pBegin->data;
                m_pBegin = m_pBegin->pnext;
                ~t->data;
                t->pnext = nullptr;
            }
            if (m_pBegin == nullptr) {
                m_pEnd = nullptr;
            }
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            if (!it.isValid()) return;
            leaf* p = it.getLeaf();

            leaf* pprev = 0;
            if (p == m_pBegin) {
                m_pBegin = p->pnext;
                it.setLeafPreBegin(m_pBegin);
            } else {
                // find prev element
                pprev = m_pBegin;
                while (pprev != 0) {
                    if (pprev->pnext == p) break;
                    pprev = pprev->pnext;
                }
                it.setLeaf(pprev);
            }
            if (pprev != 0) pprev->pnext = p->pnext;
            if (!p->pnext)  // in the end
                m_pEnd = pprev;
            p->pnext = 0;
            delete p;
            p = 0;
        }

        int getSize()
        {
            leaf* tmp = m_pBegin;
            int ans = 0;
            while (tmp != nullptr) {
                tmp = tmp->pnext;
                ++ans;
            }
            return ans;
        }

        void clear()
        {
            while (m_pBegin != nullptr) {
                popFront();
            }
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

    template<class T>
    class CDualLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev, leaf * _pnext)
            {
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
            {
            }

            CIterator(leaf *p)
            {
            }

            CIterator(const CIterator &src)
            {
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
            }

            bool operator != (const CIterator&  it) const
            {
            }

            void operator++()
            {
            }

            void operator--()
            {
            }

            T& getData()
            {
                T tmp;
                return tmp;
            }

            T& operator* ()
            {
                T tmp;
                return tmp;
            }

            leaf* getLeaf()
            {
                return 0;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
            }

            bool isValid() {
                return false;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList()
        {
        };

        virtual ~CDualLinkedList()
        {
        };

        void pushBack(T& data)
        {
        }

        T popBack()
        {
            T tmp;
            return tmp;
        }

        void pushFront(T& data)
        {
        }

        T popFront()
        {
            T tmp;
            return tmp;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
        }

        int getSize()
        {
            return 0;
        }

        void clear()
        {
        }

        CIterator begin()
        {
            return CIterator();
        }

        CIterator end()
        {
            return CIterator();
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2022_02_03

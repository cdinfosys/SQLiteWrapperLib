#if !defined SQLITE_OBJECTBB0AB32CCFEF460D816674433F5C255D
#define SQLITE_OBJECTBB0AB32CCFEF460D816674433F5C255D

#include <sqlite3.h>

namespace sqlitelib
{
    namespace SQLite3
    {
        template <typename  T> class sqlite_object
        {
            private:
                T _object;

            public:
                sqlite_object();
                ~sqlite_object();

            public:
                operator T&();
        };

        template<typename T> sqlite_object<T>::sqlite_object()
        {
        }

        template<typename T> sqlite_object<T>::~sqlite_object()
        {

            sqlite3_free(this->_object);
        }

        template<typename T> sqlite_object<T>::operator T&()
        {
            return this->_object;
        }
    } // namespace SQLite3
} // namespace sqlitelib

#endif // SQLITE_OBJECTBB0AB32CCFEF460D816674433F5C255D

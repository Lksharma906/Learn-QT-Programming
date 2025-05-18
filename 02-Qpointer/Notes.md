# Why Qpointer

- A guarded pointer, QPointer\<T>, behaves like a normal C++ pointer T *, except that it is automatically cleared when the referenced object is destroyed (unlike normal C++ pointers, which become "dangling pointers" in such cases). T must be a subclass of QObject.
- Guarded pointers are useful whenever you need to store a pointer to a QObject that is owned by someone else, and therefore might be destroyed while you still hold a reference to it. You can safely test the pointer for validity.


## Second Level Heading



### Reinterant & thread safe

- A **thread-safe** function can be called simultaneously from multiple threads, even when the invocations use shared data, because all references to the shared data are serialized.
- A **reentrant** function can also be called simultaneously from multiple threads, but only if each invocation uses its own data.

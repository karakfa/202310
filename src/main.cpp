#include <chrono>
#include <iostream>
#include <thread>


using namespace std::chrono_literals;


int main() {


  struct RequestParams {    
    std::string name;
    int value;
  };
  
  // this is at the namespace level...
  thread_local static std::unique_ptr<RequestParams> paramsPtr = nullptr;

  // Create two threads to handle two concurrent requests
  std::thread t1([]() {

    // at the initializion step of the request handling, store the request params in app context
    RequestParams rp = {std::string("Request A"),0};
    paramsPtr.reset(&rp);
    // paramsPtr.reset(new RequestParams(std::string("Request A"),0));

    for (int i = 0; i < 10; i++) {     
      std::this_thread::sleep_for(10ms);
      paramsPtr->value++;
      std::cout << paramsPtr->name << ": " << paramsPtr->value << std::endl;
    }
  });

  std::thread t2([]() {
    
    RequestParams rp = {std::string("Request B"),0};
    paramsPtr.reset(&rp);

    for (int i = 0; i < 10; i++) {
      std::this_thread::sleep_for(17ms);
      paramsPtr->value++;
      std::cout << paramsPtr->name << ": " << paramsPtr->value << std::endl;
    }
  });

  t1.join();
  t2.join();

  if(paramsPtr) {
    std::cout << paramsPtr->name << ": " << paramsPtr->value << std::endl; 
  } else {
    std::cout << "Params no more..." << std::endl; 
  }

  return 0;
}
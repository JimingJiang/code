#include<iostream>
#include<string>
#include<cstdlib>
#include<dlfcn.h>

using namespace std;


int main()
{
	void *handle = dlopen("../libhello/libhello.so", RTLD_LAZY);
	if(!handle){
		cerr<<dlerror()<<endl;
		exit(1);
	}
	typedef string (*pfunc)();		
	pfunc pdesc = (pfunc)dlsym(handle, "desc");
	char *err;
	if((err = dlerror())!=NULL){
		cerr<<err<<endl;
		exit(1);	
	}
	cout<<pdesc()<<endl;
	dlclose(handle);
	return 0;	
}

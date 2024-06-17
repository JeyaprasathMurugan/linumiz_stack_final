########################## tested in ubuntu only ##########################

steps to install the jp_stack(my version of pushd popd implementation in C)


1)after cloning from git or downloading git open the terminal in the same folder

2)then put the compiler command "gcc -o pop_helper pop_helper.c"   ##this should not be changed as further code depends on this name of the executable

3)then to access the executable globally
   i)"sudo mv pop_helper /usr/local/bin/"
   ii)"source ~/.bashrc"
   
4)then on the terminal where C files are present opent the terminal

5)run "gcc -o linumiz_stack last_read.c" 

6)then to access the executable globally
   i)"sudo mv linumiz_stack /usr/local/bin/"
   ii)"source ~/.bashrc"
   
7)then in terminal of your choice run "sudo linumiz_stack JP_INIT"      ##this is very important because this initializes the stack files and must be done to start the stack.

8)then to push put "sudo linumiz_stack jp_push address ".

9)then to pop put "sudo linumiz_stack jp_pop".



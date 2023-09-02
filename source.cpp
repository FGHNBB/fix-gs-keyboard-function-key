#include<iostream>
#include<cstdio>
#include<string.h>
#include<unistd.h>
using namespace std;

char install[30] = "install";
char uninstall[30] = "uninstall";
char error1[30] = "Too Much Arguments!";
char error2[30] = "Not Enough Arguments!";
char dest[50];

bool IsRoot()
{
  if (geteuid() == 0)
    return true;
  else
    return false;
}

void install_command()
{
  system ("mkdir /sys/module/hid_apple");
  system ("mkdir /sys/module/hid_apple/parameters");
  system ("echo 2 | tee /sys/module/hid_apple/parameters/fnmode");
  system ("echo options hid_apple fnmode=2 | tee -a /etc/modprobe.d/hid_apple.conf");
  system ("mkinitcpio -P");
}
void uninstall_command()
{
  system ("rm /sys/module/hid_apple/parameters/fnmode");
  system ("rm /etc/modprobe.d/hid_apple.conf");
  system ("mkinitcpio -P");
}

int main(int argc,char **argv)
{
  if (!IsRoot())
  {
    printf("%s\n","Please Run As ROOT!");
    return 0;
  }

  if (argc > 2) {printf("%s\n",error1);return 0;}
  if (argc < 2) {printf("%s\n",error2);return 0;}

  strcpy (dest,argv[1]);
  if (strcmp (dest,install) == 0)
    install_command();
  else if (strcmp (dest,uninstall) == 0)
    uninstall_command();
  else printf("%s\n","Error!");

  return 0;
}
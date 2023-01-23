#include <stdio.h>
#include <stdlib.h>

int main()
{
    if (system("sudo pacman -Syu") != 0)
    {
        printf("UPDATE FAILED.\n");
        exit(1);
    }
    if (system("sudo mkinitcpio -P") != 0)
    {
        printf("KERNEL BUILD FAILED.\n");
        exit(1);
    }
    if (system("sudo grub-mkconfig") != 0)
    {
        printf("GRUB INSTALL FAILED.\n");
        exit(1);
    }

    return 0;
}
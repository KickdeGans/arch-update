#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_info()
{
    system("pacman --version");
    system("mkinitcpio --version");
    system("grub-install --version");

    printf("\n\n");
}
void parse_args(int argc, char* argv[])
{
    if (argc == 1)
    {
        if (getuid())
        {
            printf("An update requires root privileges.\n");
            exit(1);
        }

        print_info();

        if (system("yes | sudo pacman -Syu") != 0)
        {
            printf("\n\033[0;31mUPDATE FAILED.\033[0;37m\n");
            exit(1);
        }
        if (system("sudo mkinitcpio -P") != 0)
        {
            printf("\n\033[0;31mKERNEL BUILD FAILED.\033[0;37m\n");
            exit(1);
        }
        if (system("set -e && exec grub-mkconfig -o /boot/grub/grub.cfg \"$@\"") != 0)
        {
            printf("\n\033[0;31mGRUB INSTALL FAILED.\033[0;37m\n");
            exit(1);
        }
    }

    int sync = 0;
    int ignore_errors = 0;
    int help = 0;
    int nvidia_install = 0;
    int fix_kernel = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--sync") == 0)
        {
            sync = 1;

            continue;
        }
        if (strcmp(argv[i], "--ignore-errors") == 0)
        {
            ignore_errors = 1;

            continue;
        }
        if (strcmp(argv[i], "--help") == 0)
        {
            help = 1;

            continue;
        }
        if (strcmp(argv[i], "--nvidia-install") == 0)
        {
            nvidia_install = 1;

            continue;
        }
        if (strcmp(argv[i], "--fix-kernel") == 0)
        {
            fix_kernel = 1;

            continue;
        }
        else
        {
            printf("Option '%s' not understood.\n", argv[i]);
            exit(1);
        }
    }

    if (fix_kernel)
    {
        if (system("yes | sudo pacman -Syy mkinitcpio linux && set -e && exec grub-mkconfig -o /boot/grub/grub.cfg") != 0)
        {
            printf("\n\033[0;31mKERNEL FIX FAILED.\033[0;37m\n");
            exit(1);
        }
        exit(0);
    }

    if (nvidia_install)
    {
        if (system("yes | sudo pacman -S lib32-nvidia-utils lib32-opencl-nvidia opencl-nvidia nvidia nvidia-utils && sudo nvidia-modprobe") != 0)
        {
            printf("\n\033[0;31mNVIDIA INSTALL FAILED.\033[0;37m\n");
            exit(1);
        }
    }

    if (ignore_errors)
    {
        if (getuid())
        {
            printf("An update requires root privileges.\n");
            exit(1);
        }

        print_info();

        if (sync)
        {
            system("yes | sudo pacman -Syyu");
        }
        else
        {
            system("yes | sudo pacman -Syu");
        }

        system("sudo mkinitcpio -P");

        system("set -e && exec grub-mkconfig -o /boot/grub/grub.cfg \"$@\"");
    }

    if (sync && !ignore_errors)
    {
        if (getuid())
        {
            printf("An update requires root privileges.\n");
            exit(1);
        }

        print_info();

        if (system("yes | sudo pacman -Syu") != 0)
        {
            printf("\n\033[0;31mUPDATE FAILED.\033[0;37m\n");
            exit(1);
        }
        if (system("sudo mkinitcpio -P") != 0)
        {
            printf("\n\033[0;31mKERNEL BUILD FAILED.\033[0;37m\n");
            exit(1);
        }
        if (system("set -e && exec grub-mkconfig -o /boot/grub/grub.cfg \"$@\"") != 0)
        {
            printf("\n\033[0;31mGRUB INSTALL FAILED.\033[0;37m\n");
            exit(1);
        }
    }

    if (help)
    {
        printf("arch-update help menu:\n    ");
        printf("--help:\n       ");
        printf("Open help menu.\n    ");
        printf("--sync:\n        ");
        printf("Sync packages too.\n    ");
        printf("--ignore-errors:\n        ");
        printf("Ignore all errors and continue.\n    ");
        printf("--nvidia-install:\n        ");
        printf("Install proprietary nvidia drivers\n    ");
        printf("--fix-kernel:\n        ");
        printf("Fix kernel\n");
    }
}
int main(int argc, char* argv[])
{
    parse_args(argc, argv);

    return 0;
}
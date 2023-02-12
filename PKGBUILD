pkgver=1.0
pkgrel=1
license=('GPLv2')
pkgname="arch-update"
pkgdesc="Tool for updating Arch Linux safely"
arch=('any')
url="https://github.com/KickdeGans/arch-update.git"
makedepends=('gcc' 'git' 'make')
optdepends=()
provides=('arch-update')

package()
{
    git clone $url

    cd arch-update

    make
    sudo make install

    cd ..

    rm -rf ./arch-update
}
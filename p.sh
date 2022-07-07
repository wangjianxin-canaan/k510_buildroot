#!/bin/bash
set -x

function usage()
{
cat << EOF
usage:
$0 linux pre_init
$0 linux gen_and_copy_patch
$0 linux check_patch
$0 uboot pre_init
$0 uboot gen_and_copy_patch
$0 uboot check_patch
EOF
exit 1
}


function gen_code()
{
#git pull
pwd
rm -rf ${tmp};mkdir -p ${tmp}
pkg_tar="$(ls dl/${pkg}/ | grep tar)"
tar -xf dl/${pkg}/${pkg_tar} -C ${tmp}
pkg_untar_name="$(ls ${tmp})"
${patch_scrip} ${tmp}/${pkg_untar_name} ${patch_dir} \*.patch \*.patch.riscv64

 
return $?
}


function gen_repo()
{
gen_code || { echo "error \n"; exit 1;}
cd "${tmp}/$(ls ${tmp})"
git init
git add -f .
git commit -a -m "init"
echo "plese enter $(pwd) modify code "
touch .stamp_downloaded  .stamp_extracted   .stamp_patched
mkdir .vscode
cp ~/tools/settings.json .vscode
}



function gen_and_copy_patch()
{
cd "${tmp}/$(ls ${tmp})"
rm -rf *.patch

last_patch_id="$(ls ${sdk_root}/package/patches/${pkg}/ | sort -nr | head -n1 | cut -d- -f1)"
#cur_patch_id="$((${last_patch_id} +1 ))"
cur_patch_id="$(expr ${last_patch_id} + 1 )"
git format-patch --no-renames -1 --start-number ${cur_patch_id}

patch_name="$(ls *.patch -t | head -n1)"

cp ${patch_name} ${patch_dir}

echo "patch file is ${patch_dir}/${patch_name}"
echo "plseare commit ${pkg} patch"
}


[ $# -ge 2 ] || usage
[ $1 = "linux" ] || [ $1 = "uboot" ] || usage
[ $2 = "pre_init" ] || [ $2 = "gen_and_copy_patch" ] || [ $2 = "check_patch" ] || usage

[ -d buildroot-2020.02.11 ] || { echo "error ! please enter sdk dir \n"; exit 1; }

pkg=$1
action=$2





sdk_root=$(pwd)
tmp="${sdk_root}/patch_tmp"
patch_scrip="${sdk_root}/buildroot-2020.02.11/support/scripts/apply-patches.sh"
patch_dir="${sdk_root}/package/patches/${pkg}"



if [ ${action} = "pre_init" ]; then
gen_repo
elif [ ${action} = "gen_and_copy_patch" ];then
gen_and_copy_patch
elif [ ${action} = "check_patch" ];then
gen_code
else
usage
fi

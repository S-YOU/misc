# ���夣�⎤�㎫�⎷�⎹��妢�㎩�⎤���妫�㎪

## ��骩

* [filesystem-ts](https://github.com/cplusplus/filesystem-ts)
* [N3505:Filesystem Library Proposal(Revision 4)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3505.html)
* [Rapperswil��ꎭ���Ꭷ�Ꭾ�����](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4080.html)

## �������

C++��莺�妫�⎤���妫�㎪�Ꭻ���夣�⎤�⎹��掽��̤���墰�⎤�㎳�⎿���天�㎼�⎹������������倂

## 쨤ꎦ�

* C++�Ꭷ�⎹�⎯�㎪������Ꭾ�����Ꭺ갲窪�Ꭷ�즺耎��Ꭾ�������夣�⎤�㎫��掽������������墭��������
    * ����妾�⎸�㎧�㎳�ᎮC++�Ꭿ��夥�㎬�⎯��妬��掽�墬�Ꭹ�����������Ꭶ��墬��倂
* Boost�㎩�⎤���妫�㎪������㎼�⎹�Ꭻ�����������鎨�玺���Ꭿ[VC](http://msdn.microsoft.com/en-us/library/hh874694.aspx)�Ꭻ��ꎣ�����墨�������

## Boost Filesystem�Ꭾ�Ꭸ�Ꭾ�����

* Boost�Ꭿ���夣�⎤�㎫��墬�Ꭹ�Ꭻchar���墰���玭������掽����値掻�墰�⎨�㎳�⎳�㎼��夥�㎳�⎰�Ꭿcodecvt���掽����倂
* ���墰�㎩�⎤���妫�㎪�Ꭷ�Ꭿlocale���掽����値����ݶTF-8���夷���妾������値���Ꭱ��墰������掾���莩�Ꭷ���Ȫ���墢�������

## ���夻�Ꭾ��夸�⎤�㎳

* ����ڧ�Ꭾnarrow character���貳�᫪O�������墰C/C++�㎩�⎤���妫�㎪���莳����获��������ꎾ�������ꎦ����������
    * POSIX�Ꭺ���har���, Windows�Ꭿchar�����wide���墭ꦲ�����墨�������
* 轴���Ꭷ�Ꭾ�Ꭻ케𸎳���墨��掺���Ꭿ���墰�Ꮎ�Ꮎ迎���墡��墱���倂
* �즺耎��Ꭾ���뎡�墭�����Ꭳ�Ꭶ��掺���Ꭿchar16_t���har32_t�⧶TF-8���掽����墡��墢�������

## ���

* �걎����夻 : �����轎���墰��玠���Ꭺ���墭���夣�⎤�㎫�Ꭾ迺鎽�����鲻��墩������玠��
* 쯎�����⎹ : �⎷�㎳���妬��失�㎪�㎳�⎯��.��..�������Ꮎ�Ꭺ��鎵��걎����夻
* ��夥�㎬�⎯��妬 : ���夣�⎤�㎫��掻�墰��夥�㎬�⎯��妬�⎨�㎳��妬��玠������������墰�����Ꭻ�쎯���������⎡�⎤�㎫
* ���夣�⎤�㎫ : �㎦�㎼�⎶��夹�⎹��妢��妾�⎿���掿�����������夣�⎤�㎫�⎷�⎹��妢�Ꭾ躎��Ꭻ����걎�𳎡�鎩
𬎭���墢���ֺ��墡��墩���������Ꮎ������Ꭺ��耎�������Ꭴ���
* ���夣�⎤�㎫�⎷�⎹��妢 : ���夣�⎤�㎫�Ꭸ�������墰��耎��Ꭾ�����
* ��ʲ�Ꭾ�⎹�㎬���������㎭�⎻�⎹�������墭����걎�𳎡�鎩���玤��ֶ������Ꭸ�㎬�㎼�⎹�Ꭻ�Ꭺ��
* ���夣�⎤�㎫��� : ���夣�⎤�㎫�Ꭾ���� .��..�Ꭿ�鎹�莥�Ꭺ���µ������Ꭴ��莬���Ꭾ��墰�ᎯOS���玭�
    * ���夣�⎤�㎫��墭迎��������玭�
    * 迎��������夣�⎤�㎫���
    * �鎹�莥�Ꭺ���夣�⎤�㎫���
    * ꦎ����玭�现���������쎺�莥����������Ꭺ����
    * ���夣�⎤�㎫�Ꭾ���倢���⎣�㎬�⎯��妬��墬�Ꭹ�鎹�莥�Ꭺ�㎫�㎼�㎫
* �㎪�㎳�⎯ : ���夣�⎤�㎫��墭���������Ꭵ�������墡��夥�㎬�⎯��妬�⎨�㎳��妬
* native�⎨�㎳�⎳�㎼��夥�㎳�⎰
* NTCTS(Null-Terminated Character-Type Sequence�Ꭾ����)
* OS���玭�
* 𨎪��夥�㎬�⎯��妬 : ������夥�㎬�⎯��妬�Ꭻ걎����墨����������������夥�㎬�⎯��妬 ..�Ꭷ�������
.��..�Ꭻ�Ꭿ�Ꭹ��������Ꭺ��
* ���夻 : (�㎫�㎼����)_opt (�㎫�㎼�����⎣�㎬�⎯��妬)_opt ���夣�⎤�㎫��墰��
* ���夻�������?(pathname resolution) OS���玭�
see [POSIX : Pathname Resolution](http://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap04.html#tag_04_11)

# �掻��
char, wchar_t, char16_t, char32_t����ncoded���玭�����Ꭸ����(signed char���nsigned char�Ꭿ�厥��墬��)���
template���妫�㎡�㎼�⎿�ᎮcharT�Ꭿ�������墰��墣�Ꭾ�Ꭹ�����Ꭷ�������

# ����������夣�⎤�㎫<filesystem>

躎��Ꭺ�⎯�㎩�⎹��莧�뀎�迓
```
namespace std { namespace tbd { namespace filesystem {
    class path;
    class filesystem_error;
    class directory_entry;
    class directory_iterator;
    class recursiev_directory_iterator;
    class file_type;
    class perms;
    class file_status;
    struct space_info;
    enum class copy_options;
    enum class directory_options;
    file_time_type;
}}}
```
躎��Ꭺ��������
찬墫�Ꭾ���������Ꭿ�⎨�㎩�㎼�⎳�㎼���rror_code ec���ꎿ������妾�⎸�㎧�㎳�Ꭸ���玤�������������㎼�⎸�㎧�㎳�Ꭾ2������������������

* ���玤����㎼�⎸�㎧�㎳ : void copy(const path& from, const path& to);
* �⎨�㎩�㎼���ꎿ������妾�⎸�㎧�㎳ : void copy(const path& from, const path& to,error_code& ec) noexcept;

```
path absolute(const path& p, const path& base=current_path());
path canonical(const path& p, const path& base = current_path());
void copy(const path& from, const path& to);
bool copy_file(const path& from, const path& to);
void copy_symlink(const path& existing_symlink,const path& new_symlink);
bool create_directories(const path& p);
bool create_directory(const path& p);
void create_directory_symlink(const path& to,const path& new_symlink);
void create_hard_link(const path& to, const path& new_hard_link);
void create_symlink(const path& to, const path& new_symlink);
path current_path();
void current_path(const path& p);
bool exists(file_status s) noexcept;
bool exists(const path& p);
bool equivalent(const path& p1, const path& p2);
uintmax_t file_size(const path& p);
uintmax_t hard_link_count(const path& p);
bool is_block_file(file_status s) noexcept;
bool is_block_file(const path& p);
bool is_character_file(file_status s) noexcept;
bool is_character_file(const path& p);
bool is_directory(file_status s) noexcept;
bool is_directory(const path& p);
bool is_empty(const path& p);
bool is_fifo(file_status s) noexcept;
bool is_fifo(const path& p);
bool is_other(file_status s) noexcept;
bool is_other(const path& p);
bool is_regular_file(file_status s) noexcept;
bool is_regular_file(const path& p);
bool is_socket(file_status s) noexcept;
bool is_socket(const path& p);
bool is_symlink(file_status s) noexcept;
bool is_symlink(const path& p);
file_time_type last_write_time(const path& p);
void last_write_time(const path& p, file_time_type new_time);
path read_symlink(const path& p);
bool remove(const path& p);
uintmax_t remove_all(const path& p);
void rename(const path& from, const path& to);
void resize_file(const path& p, uintmax_t size);
space_info space(const path& p);
file_status status(const path& p);
bool status_known(file_status s) noexcept;
file_status symlink_status(const path& p);
path system_complete(const path& p);
path temp_directory_path();
path unique_path(const path& model="%%%%-%%%%-%%%%-%%%%");
```

# class path
class path�Ꭿ���夻����𣎨���失�㎩�⎹���
���墰���夻��玮�����Ꭻ���ت����������⎹����valid�Ꭷ�������ꎦ�墱�Ꭺ��倂
```
namespace std { namespace tbd { namespace filesystem {

class path {
public:
    typedef see below value_type;
    typedef basic_string<value_type> string_type;
    static constexpr value_type preferred_separator = see below;
    ...
private:
    string_type pathname; // exposition only
};
}}}
```
value_type�ᎯOS��玮�����Ꭻ迎����ncoded���玭�������
POSIX�Ꭺ���alue_type=char�Ꭷpreferred_separator=/���
Windows�Ꭺ���alue_type=wchar_t�Ꭷpreferred_separator=\���

## path���

```
pathname:
  root-name root-directory_opt relative-path_opt
  root-directory relative-path_opt
  relative-path
```

* root-name : �걎����夻���ꎡ����ѰS���玭�墰��簧���������������
���墪��墲c:�Ꭸ�ᵽ\�Ꭸ��倂

```
root-directory:
  directory-separator

relative-path:
    filename
    relative-path directory-separator
    relative-path directory-separator filename

filename:
    name
    dot
    dot-dot

name:
    directory-seprator轎���墰OS���玭�墰���玭�墰��

dot : .
dot-dot : ..
slash : /

directory-separator:
    slash
    slash directory-separator
    preferred-separator
    preferred-separator directory-separator

preferred-separator:
    OS���玭�墰��夥�㎬�⎯��妬�⎻���妮�㎼�⎿���lash�Ꭾ������倂
```
* ����������ꎤ��ʲ�Ꭾdirectory-separator�Ꭿ躀�Ꭴ�Ꭾdirectory-separator�Ꭸ�墬���倂
* .�Ꭸ�������夣�⎤�㎫��墱�⎫�㎬�㎳�����⎣�㎬�⎯��妬���鎤�����倂
* ..�Ꭿ𨎪��夥�㎬�⎯��妬���鎤�����倂
* �鎹��墰OS�Ꭻ�Ꭸ�Ꭳ�Ꭶ�鎹�莥�Ꭺ���µ������Ꭴ�鎹�莥�Ꭾ���夣�⎤�㎫������墥�Ꭶ�������

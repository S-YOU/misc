# 躎���(parallel)���妯�⎰�㎩���妵�⎰

## ��骩

* [parallelism-ts](https://github.com/cplusplus/parallelism-ts)

## �������

C++��莺�妫�⎤���妫�㎪�Ꭻ������Ꭻ���������Ꭶ����躎�������㎭�⎰�㎩���妵�⎰���现�窧��������

## 쨤ꎦ�

* ���������std::experimental::parallel::v1`�ᎫExecutionPolicy���妫�㎡�㎼�⎿������Ꭴ����������妵���妮�㎼���������ꎠ��������
* ����������夣�⎤�㎫�Ꭿ`meow`���
* 躎����夤�㎫�⎴�㎪�⎺�㎠�Ꭿ�鎴���⎢�⎯�⎻�⎹���������ȳ�Ꭷ���ʲ�Ꭻ�⎢�⎯�⎻�⎹��������

## ��ꎡ����㎪�⎷�㎼

���

    std::vector<int> v = ...

    // �������墰�⎽�㎼��
    std::sort(v.begin(), v.end());

    // 躎������
    using namespace std::experimental::parallel;

    // �⎷�㎼�⎱�㎳�⎷�㎣�㎫�⎽�㎼��(����ڧ�Ꭾ�⎽�㎼��)�������
    sort(seq, v.begin(), v.end());

    // 躎����夿�㎼����𪎱�
    sort(par, v.begin(), v.end());

    // ���失��妭���墪躎����夿�㎼����𪎱�
    sort(par_vec, v.begin(), v.end());

    // ���妬�⎷�㎼�Ꭾ��ꎡ�������������
    size_t threshold = ...
    execution_policy exec = (v.size() > therashold) ? para : seq;
    sort(exec, v.begin(), v.end());


## �������`<experimental/execution_policy>`

    namespace std {
    namespace experimental {
    namespace parallel {
    inline namesapce v1 {

    template<class T> struct is_execution_policy;
    template<class T> constexpr bool is_execution_policy_v
      = is_execution_policy<T>::value;

     class sequential_execution_policy;
     class parallel_execution_policy;
     class parallel_vector_execution_policy;
     class execution_policy;
     }}}}

is_execution_policy�Ꭿ�Ꭹ�Ꭾ���妬�⎷�㎼�Ꭾ躎����玮�ꎡ������������玮�����倂

* sequential_execution_policy
    躎����玮�ꎡ����Ꭶ�Ꭿ�����Ꭺ�����Ꭸ���鎤����
* parallel_execution_policy
    躎����玮�ꎡ����Ꭶ�������墪���鎤����
* parallel_vector_execution_policy
    ���失��妭���墪躎����玮�ꎡ����Ꭶ�������墪���鎤����
* execution_policy
    ��ꎡ�����Ꭻ���妬�⎷�㎼���莱����������

## 躎����玮�ꎡ�����Ꭾ�쎯������

* ��ꎡ�掸���Ꭻ���ꎦ�墬�㎡�㎢�㎪��墬������Ꮀstd::bad_alloc�������������
* �鎴���⎢�⎯�⎻�⎹����������掾�玤����玺���墡�Ꭸ��
    * ��ꎡ����㎪�⎷�㎼���arallel_vector_execution_policy�Ꭺ���td::terminate����¾�Ꮆ���
    * ��ꎡ����㎪�⎷�㎼���equential_execution_policy���arallel_execution_policy�Ꭺ��
      exception_list�������������
* 躎����夤�㎫�⎴�㎪�⎺�㎠���td::bad_alloc��������墨掺������墰�Ꭷ�Ꭺ������Ꮀ�����Ꮉ�Ꭶ�Ꭾ���玤�墱���玺��墭����������倂
  ���玤������������������Ꭸ��掸�����夤�㎫�⎴�㎪�⎺�㎠�����Ꭾ�Ꮎ�Ꮎ������������墩�Ꭺ�����Ꭿ躺玮�倂

## exception_list

    class exception_list : public exception {
    public:
        typedef unspecified iterator;
        size_t size() const noexcept;
        iterator begin() const noexcept;
        iterator end() const noexcept;
        const char *what() const noexcept override;
    };

* iterator�ᎯForwardIterator;
* size()�Ꭿexception_list�����Ꭴ�⎪���夺�⎧�⎯��墰���ʲ
* begin(), end()�����Ꭾ�⎪���夺�⎧�⎯��墰�ִ
* what()�Ꭿ����NTBS(NULL鎫�����玭���)���ꎿ������

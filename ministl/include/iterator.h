#pragma once

#include <cstddef>
namespace ministl {

struct false_type {};
struct true_type {};

/**
Input Iterator               read only
Output Iterator              write only
Forward Iterator             允许"写入型"算法在其指向区间进行操作
Bidirectional Iterator       提供双向访问能力
Random Access Iterator       支持原生指针具有的全部能力
*/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


}  // namespace ministl
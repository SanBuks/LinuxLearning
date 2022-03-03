#include <cctype>
#include <iostream>
#include <climits>

/**
 * 判断补数加法是否溢出
 * @param x 第一个数
 * @param y 第二个数
 * @return 0: 正常
 *         1: 上溢
 *        -1: 下溢
 */
int tadd_ok(long x, long y) {
  auto t = x + y;
  if (x > 0 && y > 0 && t < 0) {
    return 1;
  } else if (x < 0 && y < 0 && t >= 0) {
    return -1;
  } else {
    return 0;
  }
}

/**
 * 判断补数乘法是否溢出
 * @param x 第一个数
 * @param y 第二个数
 * @return 0: 正常
 *         1: 上溢
 *        -1: 下溢
 */
int tmul_ok(long x, long y) {
  long t = x * y;
  if (!x || t / x == y) {
    return 0;
  } else if ((x < 0 && y < 0) || (x > 0 && y > 0)) {
    return 1;
  } else {
    return -1;
  }
}

/**
 * 解析数字
 * @param str 指向数字的字符指针
 * @param parse_base 基数
 * @return 解析值 / -1 代表解析失败
 */
int parseNumber(const char * __restrict__ str, int parse_base) {
  if (std::isdigit(*str)) {
    if ((*str - '0') < parse_base) {
      return *str - '0';
    }
  } else if (std::isupper(*str)) {
    if ((*str - 'A') + 10 < parse_base) {
      return *str - 'A' + 10;
    }
  } else if (std::islower(*str)) {
    if ((*str - 'a') + 10 < parse_base) {
      return *str - 'a' + 10;
    }
  }
  return -1;
}

/**
 * 自定义 strtol
 * 注意复杂类型
 * const char * *p              -> pointer to pointer to const char
 * const char * const *p        -> pointer to const pointer to const char
 * const char * const * const p -> const pointer to const pointer to const char
 */
long my_strtol(const char * __restrict__ str,
               const char ** __restrict__ str_end, int base) {
  // 是否是正数
  bool positive = true;
  // 基数
  int parse_base = base;
  // 总和
  long sum = 0;
  // 解析数字的绝对值
  int abs = 0;

  // 0. 处理退化情况
  // 0.1 处理 base 非法值
  if (base < 0 || base > 36 || base == 1) {
    goto exit;
  }
  // 0.2 处理 str 非法值
  if (!str || *str == '\0') {
    goto exit;
  }

  // 1. 略去前置 空白符
  while (isspace(*str)) {
    if (str_end) {
      *str_end = str;
    }
    ++str;
  }
  if (*str == '\0') {
    goto exit;
  }

  // 2. 判断是否有正负号
  if (*str == '-') {
    positive= false;
    if (str_end) {
      *str_end = str;
    }
    ++str;
  } else if (*str == '+'){
    if (str_end) {
      *str_end = str;
    }
    ++str;
  }
  if (*str == '\0') {
    goto exit;
  }

  // 3. 判断是否有进制标志
  if (*str == '0' &&
      *(str + 1) != '\0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    if (base == 0 || base == 16) {
      parse_base = 16;
      if (str_end) {
        *str_end = str + 1;
      }
      str += 2;
    }
  } else if (*str == '0') {
    if (base == 0 || base == 8) {
      parse_base = 8;
      if (str_end) {
        *str_end = str;
      }
      str += 1;
    }
  }
  if (*str == '\0') {
    goto exit;
  }

  // 4. 解析处理数字
  while (-1 != (abs = parseNumber(str, parse_base))) {
    if (!positive) {
      abs = - abs;
    }
    // 4.1 处理乘法溢出
    auto is_overflow = tmul_ok(sum, parse_base);
    if (is_overflow < 0) {
      errno = ERANGE;
      if (str_end) {
        *str_end = str;
      }
      return LONG_MIN;
    } else if (is_overflow > 0) {
      errno = ERANGE;
      if (str_end) {
        *str_end = str;
      }
      return LONG_MAX;
    } else {
      sum *= parse_base;
    }
    // 4.2 处理加法溢出
    is_overflow = tadd_ok(sum, abs);
    if (is_overflow < 0) {
      errno = ERANGE;
      if (str_end) {
        *str_end = str;
      }
      return LONG_MIN;
    } else if (is_overflow > 0) {
      errno = ERANGE;
      if (str_end) {
        *str_end = str;
      }
      return LONG_MAX;
    } else {
      sum += abs;
    }

    if (str_end) {
      *str_end = str;
    }
    str++;
    if (*str == '\0') {
      goto exit;
    }
  }

exit:
  if (str_end) {
    *str_end = str;
  }
  return sum;
}


void test1() {
  printf("\"1010\" in binary  --> %ld\n", my_strtol("1010", nullptr, 2));
  printf("\"12\"   in octal   --> %ld\n", my_strtol("12",   nullptr, 8));
  printf("\"A\"    in hex     --> %ld\n", my_strtol("A",    nullptr, 16));
  printf("\"junk\" in base-36 --> %ld\n", my_strtol("junk", nullptr, 36));
  printf("\"012\"  in auto-detected base --> %ld\n", my_strtol("012",  nullptr, 0));
  printf("\"0xA\"  in auto-detected base --> %ld\n", my_strtol("0xA",  nullptr, 0));
  printf("\"junk\" in auto-detected base --> %ld\n", my_strtol("junk", nullptr, 0));
}

void test2() {
  const char *p = "10 200000000000000000000000000000 30 -40 junk";
  printf("Parsing '%s':\n", p);
  for (;;) {
    errno = 0;
    char *end;
    const long i = strtol(p, &end, 10);
    if (p == end) {
      break;
    }
    const bool range_error = errno == ERANGE;
    printf("Extracted '%.*s', strtol returned %ld.", (int) (end - p), p, i);
    p = end;
    if (range_error) {
      printf(" Range error occurred.");
    }
    putchar('\n');
  }
  printf("Unextracted leftover: '%s'\n\n", p);
}

int main() {
//  test1();
  test2();
//  char *end;
//  const char **e;
//  const char *p = "-21234000000000";
//  std::cout << my_strtol(p, e, 4) << "\n";
//  std::cout << **e << "\n";
//  perror("my_strtol");
////  std::cout << strtol(p, &end, 36) << "\n";
  return 0;
}
typedef enum { Less, Equal, Greater } Order;

Order intCompare(int a, int b) {
  return intWhen2
    ( a < b, Less
      , a == b, Equal
      , Greater);
}

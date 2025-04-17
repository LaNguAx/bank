# Bank — C++ OOP Mini‑Bank

Small C++11 project that models customers, accounts, and transactions via clean class design.

## ✨ Core files

| Class/File        | Highlights                                     |
|-------------------|------------------------------------------------|
| `Person`          | Holds ID, name, and basic KYC data             |
| `Account`         | Balance, interest rate, `deposit/withdraw`     |
| `Transaction`     | Timestamped money moves with enum type         |
| `Bank`            | Owns vectors of `Account`+`Person`, routes transfers, logs every `Transaction` |
| `MainTrain.cpp`   | Demo driver and unit‑test style checks         |

## 📝 Customising

* Add new transaction types by extending the `enum` in `Transaction.h`.
* Swap `std::vector` for a database adaptor if persistent storage is needed.

## ⚖️ License

MIT

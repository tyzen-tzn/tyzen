// Copyright (c) 2011-2020 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TYZEN_QT_TYZENADDRESSVALIDATOR_H
#define TYZEN_QT_TYZENADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class TyzenAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TyzenAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Tyzen address widget validator, checks for a valid tyzen address.
 */
class TyzenAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TyzenAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // TYZEN_QT_TYZENADDRESSVALIDATOR_H

// Copyright (c) 2019 The Bitcoin and Tyzen Core Authors
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TYZEN_QT_TEST_OPTIONTESTS_H
#define TYZEN_QT_TEST_OPTIONTESTS_H

#include <qt/optionsmodel.h>

#include <QObject>

class OptionTests : public QObject
{
    Q_OBJECT
public:
    explicit OptionTests(interfaces::Node& node) : m_node(node) {}

private Q_SLOTS:
    void optionTests();
    void parametersInteraction();

private:
    interfaces::Node& m_node;
};

#endif // TYZEN_QT_TEST_OPTIONTESTS_H

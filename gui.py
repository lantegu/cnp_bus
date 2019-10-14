# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'gui.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!
import sys
import networkx as nx
import matplotlib.pyplot as plt
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QApplication

import sz_bus

import numpy as np


class Ui_MainWindow(object):
    def __init__(self):
        self.node_num = 0
        self.nodes = []
        self.edges = []
        self.k_frequency = []
        self.k_num = []
        self.nodes_size=[]
        self.nodes_color=[]
        self.intention_a_count=0
        self.random_a_count=0
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(260, 140, 221, 241))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.simulation_R = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.simulation_R.clicked.connect(lambda :self.generate_simulation_R())
        self.simulation_R.setStyleSheet("QPushButton{\n"
                                        "color: rgb(255, 255, 255);\n"
                                        "background-color: rgb(0, 255, 0);\n"
                                        "}")
        self.simulation_R.setObjectName("simulation_R")
        self.gridLayout.addWidget(self.simulation_R, 4, 0, 1, 1)
        self.reset_d = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.reset_d.clicked.connect(lambda :self.generate())
        self.reset_d.setStyleSheet("QPushButton{\n"
                                   "color: rgb(255, 255, 255);\n"
                                   "background-color: rgb(0, 255, 0);\n"
                                   "}")
        self.reset_d.setObjectName("reset_d")
        self.gridLayout.addWidget(self.reset_d, 5, 1, 1, 1)
        self.degree_s = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.degree_s.clicked.connect(lambda: self.generate_degree_d())
        self.degree_s.setStyleSheet("QPushButton{\n"
                                    "color: rgb(255, 255, 255);\n"
                                    "background-color: rgb(0, 255, 0);\n"
                                    "}")
        self.degree_s.setObjectName("degree_s")
        self.gridLayout.addWidget(self.degree_s, 0, 1, 1, 1)
        self.network_s = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.network_s.clicked.connect(lambda: self.generate_network())
        self.network_s.setStyleSheet("QPushButton{\n"
                                     "color: rgb(255, 255, 255);\n"
                                     "background-color: rgb(0, 255, 0);\n"
                                     "}")
        self.network_s.setObjectName("network_s")
        self.gridLayout.addWidget(self.network_s, 0, 0, 1, 1)
        self.intention_a = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.intention_a.clicked.connect(lambda: self.generate_intention_a())
        self.intention_a.setStyleSheet("QPushButton{\n"
                                       "color: rgb(255, 255, 255);\n"
                                       "background-color: rgb(0, 255, 0);\n"
                                       "}")
        self.intention_a.setObjectName("intention_a")
        self.gridLayout.addWidget(self.intention_a, 2, 0, 1, 1)
        self.generate_d = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.generate_d.clicked.connect(lambda: self.generate_d)
        self.generate_d.setStyleSheet("QPushButton{\n"
                                      "color: rgb(255, 255, 255);\n"
                                      "background-color: rgb(0, 255, 0);\n"
                                      "}")
        self.generate_d.setObjectName("generate_d")
        self.gridLayout.addWidget(self.generate_d, 5, 0, 1, 1)
        self.others_d = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.others_d.clicked.connect(lambda :self.generate_others())
        self.others_d.setStyleSheet("QPushButton{\n"
                                    "color: rgb(255, 255, 255);\n"
                                    "background-color: rgb(0, 255, 0);\n"
                                    "}")
        self.others_d.setObjectName("others_d")
        self.gridLayout.addWidget(self.others_d, 4, 1, 1, 1)
        self.random_a = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.random_a.clicked.connect(lambda :self.generate_random_a())
        self.random_a.setStyleSheet("QPushButton{\n"
                                    "color: rgb(255, 255, 255);\n"
                                    "background-color: rgb(0, 255, 0);\n"
                                    "}")
        self.random_a.setObjectName("random_a")
        self.gridLayout.addWidget(self.random_a, 2, 1, 1, 1)
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(260, 80, 221, 51))
        self.label.setObjectName("label")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.simulation_R.setText(_translate("MainWindow", "攻击效果"))
        self.reset_d.setText(_translate("MainWindow", "重置"))
        self.degree_s.setText(_translate("MainWindow", "度分布图"))
        self.network_s.setText(_translate("MainWindow", "网络结构图"))
        self.intention_a.setText(_translate("MainWindow", "刻意攻击"))
        self.generate_d.setText(_translate("MainWindow", "生成"))
        self.others_d.setText(_translate("MainWindow", "最短路径"))
        self.random_a.setText(_translate("MainWindow", "随机攻击"))
        self.label.setText(_translate("MainWindow", "数据源：深圳市公交站点"))

    def generate_network(self):


        G = nx.Graph()
        G.add_nodes_from(list(range(self.node_num)))
        G.add_edges_from(self.edges)
        plt.figure(figsize=(80, 80), dpi=80)
        nx.draw_networkx(G, pos=nx.random_layout(G), node_size=self.nodes_size, font_size=0, width=0.3,
                         node_color=self.nodes_color)
        plt.show()

    def generate_degree_d(self):
        plt.bar(x=self.k_frequency, height=self.k_num)

        plt.show()

    def generate_intention_a(self):
        self.intention_a_count += 1
        sz_bus.create_net()
        sz_bus.intention_attack(10*self.intention_a_count)
        k_frequency = []
        k_num = []
        k_nodes=[]
        edges=[]
        nodes_color=[]
        nodes_size=[]
        d_distribution = sz_bus.degree_distribution()
        for i in range(d_distribution[0] + 1):
            if i == 0:
                continue
            if d_distribution[i] == 0:
                continue
            k_frequency.append(i)
            k_num.append(d_distribution[i])
        sz_bus.c_free(d_distribution)
        self.k_frequency=k_frequency
        self.k_num=k_num
        matrix = sz_bus.transfor_table_to_matrix()
        node_num = sz_bus.get_node_num()
        for i in range(node_num):
            count = 0
            for j in range(node_num):
                if matrix[i][j] != 0 and matrix[i][j] != 600000:
                    edges.append((i, j))
                    count += 1
            k_nodes.append(count)
        for i in k_nodes:
            if i < 2:
                nodes_color.append('y')
                nodes_size.append(1)
            elif i >= 2 and i < 5:
                nodes_color.append('b')
                nodes_size.append(3)
            else:
                nodes_color.append('r')
                nodes_size.append(5)
        self.nodes_color = nodes_color
        self.nodes_size = nodes_size
        self.edges = edges
        self.node_num= sz_bus.get_node_num()
        sz_bus.free_memory()
        print('攻击完毕')

    def generate_random_a(self):
        self.random_a_count+=1
        sz_bus.create_net()
        sz_bus.random_attack(10 * self.random_a_count)
        k_frequency = []
        k_num = []
        nodes_color=[]
        nodes_size=[]
        k_nodes=[]
        edges=[]
        d_distribution = sz_bus.degree_distribution()
        for i in range(d_distribution[0] + 1):
            if i == 0:
                continue
            if d_distribution[i] == 0:
                continue
            k_frequency.append(i)
            k_num.append(d_distribution[i])
        sz_bus.c_free(d_distribution)
        self.k_frequency=k_frequency
        self.k_num=k_num
        matrix = sz_bus.transfor_table_to_matrix()
        node_num = sz_bus.get_node_num()
        for i in range(node_num):
            count = 0
            for j in range(node_num):
                if matrix[i][j] != 0 and matrix[i][j] != 600000:
                    edges.append((i, j))
                    count += 1
            k_nodes.append(count)
        for i in k_nodes:
            if i < 2:
                nodes_color.append('y')
                nodes_size.append(1)
            elif i >= 2 and i < 5:
                nodes_color.append('b')
                nodes_size.append(3)
            else:
                nodes_color.append('r')
                nodes_size.append(5)
        self.nodes_color = nodes_color
        self.nodes_size = nodes_size
        self.edges = edges
        self.node_num = sz_bus.get_node_num()
        sz_bus.free_memory()
        print('攻击完毕')
    def generate_simulation_R(self):
        average_degree_in=[]
        average_clustering_c_in=[]
        num_of_sub_graph_in=[]
        average_degree_ra=[]
        average_clustering_c_ra=[]
        num_of_sub_graph_ra=[]
        x_list=[10*i for i in range(10)]
        sz_bus.create_net()
        average_degree_in.append(sz_bus.average_degree())
        average_degree_ra.append(sz_bus.average_degree())
        average_clustering_c_in.append(sz_bus.average_clustering_c())
        average_clustering_c_ra.append(sz_bus.average_clustering_c())
        num_of_sub_graph_in.append(sz_bus.num_of_sub_graph())
        num_of_sub_graph_ra.append(sz_bus.num_of_sub_graph())
        for i in range(1,10):
            sz_bus.create_net()
            sz_bus.intention_attack(10*i)
            average_degree_in.append(sz_bus.average_degree())
            average_clustering_c_in.append(sz_bus.average_clustering_c()*10)
            num_of_sub_graph_in.append(sz_bus.num_of_sub_graph()/100)
            sz_bus.free_memory()

        for i in range(1,10):
            sz_bus.create_net()
            sz_bus.random_attack(10*i)
            average_degree_ra.append(sz_bus.average_degree())
            average_clustering_c_ra.append(sz_bus.average_clustering_c()*10)
            num_of_sub_graph_ra.append(sz_bus.num_of_sub_graph()/100)
            sz_bus.free_memory()

        plt.xlabel('percentage')
        plt.ylabel('value')
        plt.plot(x_list,average_degree_in,marker='+',linewidth=3,linestyle='--',label='average_degree_i')
        plt.plot(x_list,average_clustering_c_in,marker='*',linewidth=3,label='average_clustering_c_i*10')
        plt.plot(x_list, num_of_sub_graph_in , linewidth=3,label='num_of_sub_graph_i/100')
        plt.plot(x_list,average_degree_ra,marker='+',linewidth=3,linestyle='--',label='average_degree_ran')
        plt.plot(x_list,average_clustering_c_ra,marker='*',linewidth=3,label='average_clustering_c_ran*10')
        plt.plot(x_list, num_of_sub_graph_ra, linewidth=3,label='num_of_sub_graph_ran/100')
        plt.legend(loc="upper right")
        plt.show()
    def generate_others(self):
        #此处的数据建议在sz_bus内运算完后拷入
        random_attack_shortest_list_bz = [7.472186088562012,12.88831615447998, 8.117074012756348, 6.154347896575928,
                                          5.117283821105957,
                                          3.071748971939087, 2.5414633750915527, 1.693333387374878, 1.5862069129943848,
                                          1.1428571939468384]
        intention_attack_shortest_list = [7.472186088562012,17.567996978759766, 5.034280776977539, 4.4801764488220215,
                                          3.2005813121795654, 3.2277579307556152, 3.4811716079711914,
                                          3.8208954334259033,
                                          2.175438642501831, 2.1764705181121826]
        random_attack_shortest_list_sz = [11.749582290649414, 13.045199394226074, 12.968573570251465,
                                          16.054622650146484,
                                          14.186345100402832, 13.511690139770508, 17.976675033569336,
                                          15.347735404968262,
                                          3.70617938041687, 1.5628741979599]
        intention_attack_shortest_list_sz = [11.749582290649414, 46.852134704589844, 22.600046157836914,
                                             9.639752388000488,
                                             3.9622790813446045, 4.094183444976807, 3.741299867630005,
                                             4.198434352874756,
                                             5.2573466300964355, 7.78861141204834]
        x_list= [ i*10 for i in range(10)]
        plt.xlabel('percentage')
        plt.ylabel('average_shortest_path')
        plt.plot(x_list, random_attack_shortest_list_bz,marker='.', label='random_attack_bz')
        plt.plot(x_list, intention_attack_shortest_list, marker='+', label='intention_attack_bz')
        plt.plot(x_list, random_attack_shortest_list_sz, marker='.',linestyle='--', label='random_attack_sz')
        plt.plot(x_list, intention_attack_shortest_list_sz, marker='+',linestyle='--', label='intention_attack_sz')
        plt.legend(loc='upper right')
        plt.show()
    def generate(self):
        sz_bus.create_net()

        edges = []
        k_frequency = []
        k_num = []
        k_nodes = []
        nodes_color = []
        nodes_size = []
        d_distribution = sz_bus.degree_distribution()
        for i in range(d_distribution[0] + 1):
            if i == 0:
                continue
            if d_distribution[i] == 0:
                continue
            k_frequency.append(i)
            k_num.append(d_distribution[i])
        sz_bus.c_free(d_distribution)
        self.k_frequency = k_frequency
        self.k_num = k_num
        matrix = sz_bus.transfor_table_to_matrix()
        node_num = sz_bus.get_node_num()
        for i in range(node_num):
            count = 0
            for j in range(node_num):
                if matrix[i][j] != 0 and matrix[i][j] != 600000:
                    edges.append((i, j))
                    count += 1
            k_nodes.append(count)
        for i in k_nodes:
            if i < 2:
                nodes_color.append('y')
                nodes_size.append(1)
            elif i >= 2 and i < 5:
                nodes_color.append('b')
                nodes_size.append(3)
            else:
                nodes_color.append('r')
                nodes_size.append(5)
        self.nodes_color=nodes_color
        self.nodes_size=nodes_size
        self.edges = edges
        self.node_num = sz_bus.get_node_num()
        sz_bus.free_memory()
        print('生成完毕')


class MyWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyWindow, self).__init__(parent)
        self.setupUi(self)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWin = MyWindow()
    myWin.show()
    myWin.generate()
    sys.exit(app.exec_())

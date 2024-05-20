# 💧 LUSO ANALYSIS
### Water Supply Network Management System

## Description
This project provides a comprehensive management system for water supply networks in Portugal.
It offers functionalities to analyze basic service metrics and assess the network's resilience to failures.


## 📊 Problem Data
Utilizing an idealized [dataset](data/large-dataSet/) representing the Portuguese continental water supply network,
the system employs a directed graph structure to model various network elements such as water `reservoirs`,
`pumping stations`, and delivery sites `cities`. The user interacts with the system through a menu-driven interface,
facilitating easy access to network analysis tools and operations.

<p align="center"><img src="docs/images/portugal_map.png" width=40%></p>
<p align="center">Image - Portugal's water system map</p>

## 🚀 Problem Motivation

### Basic Service Metrics
- **Determine Maximum Water Reach**: Calculate the maximum water flow to each city using the Edmonds-Karp algorithm.
- **Verify Network Configuration**: Assess if the existing configuration can meet all customer water needs and identify areas with deficits.
- **Load Balancing**: Develop algorithms to balance the load across the network, minimizing flow discrepancies.

### Reliability and Sensitivity to Failures
- **Reservoir Outage Impact**: Evaluate the effect of reservoir outages on delivery capacity and identify affected cities.
- **Pumping Station Maintenance**: Analyze the impact of pumping station maintenance on delivery capacity and identify affected cities.
- **Pipeline Failure Analysis**: Determine the impact of pipeline failures on water delivery to cities and identify affected areas.

## 📚 Documentation
The project includes comprehensive documentation using Doxygen, providing detailed insights into the implemented code and offering
time complexity analysis for key algorithms.

Find the complete documentation in the [Doxygen HTML Documentation](docs/output/index.html).

## 🤝 Contributors
This project was developed for the [Algorithm Design](https://sigarra.up.pt/feup/en/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=484424) course.

@ DA 2023/24 - Project 01, Group G07_9

<br>

__This project was developed for [DA](https://sigarra.up.pt/feup/en/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=520321) at @FEUP__

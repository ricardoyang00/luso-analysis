# 💧 LUSO ANALYSIS
### Water Supply Network Management System

> DA 2023/24 - Project 01, Group G07_9

This project provides a comprehensive management system for water supply networks in Portugal.

## 📊 Problem Data
Utilizing an idealized [dataset](large-dataSet/) representing the Portuguese continental water supply network, 
the system employs a directed graph structure to model various network elements such as water `reservoirs`, 
`pumping stations`, and delivery sites `cities`. The user interacts with the system through a menu-driven interface, 
facilitating easy access to network analysis tools and operations.

## 🚀 Problem Motivation

### Basic Service Metrics
- **Determine Maximum Water Reach**: Calculate the maximum water flow to each `city` using the Edmonds-Karp algorithm.
- **Verify Network Configuration**: Assess if the existing configuration can meet all customer water needs and identify areas with deficits.
- **Load Balancing**: Develop algorithms to balance the load across the network, minimizing flow discrepancies.

### Reliability and Sensitivity to Failures
- **Reservoir Outage Impact**: Evaluate the effect of reservoir outages on delivery capacity and identify affected cities.
- **Pumping Station Maintenance**: Analyze the impact of pumping station maintenance on delivery capacity and identify affected cities.
- **Pipeline Failure Analysis**: Determine the impact of pipeline failures on water delivery to cities and identify affected areas.

## ⚙️ Installation
1. **Clone the Repository**
2. **Navigate to the Project Directory**
    ```Bash
   cd feup_da_01
   ```
3. ***Create and Open Build directory***
    ```Bash
   mkdir build 
   cd build
   ```
4. ***Build the Project***
    ```Bash
   cmake ..
   cmake --build .
   ```
5. ***Execute the Program***
    ```Bash
    ./feup_da_01
   ```

## 📚 Documentation
The project includes comprehensive documentation using Doxygen, providing detailed insights into the implemented code and offering
time complexity analysis for key algorithms.

Find the complete documentation in the [Doxygen HTML Documentation](docs/output/index.html).

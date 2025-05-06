# 🎯 Final Project – 3D Laser Scanner

**Author**: Lehi Quincho M.  
**Student ID (CUI)**: 20122586  

This project is a 3D laser scanner built using **C++** and **OpenCV**, developed as part of a university-level computer graphics course. The system captures the geometry of real-world objects using a rotating platform, a line laser, and a camera, and reconstructs them into a 3D point cloud.

---

## 🛠️ How It Works

The scanner consists of a physical prototype where:
- A **line laser**, shaped using a prism, projects a vertical line onto an object placed on a rotating platform.
- As the platform rotates, the laser line deforms based on the object's surface.
- A **camera** captures each deformation frame by frame.
- These frames are processed using **OpenCV** in C++ to extract the laser line profile.
- The result is a **3D point cloud** representing the scanned object.
- For visualization, the point clouds are displayed using **tkViewer**.

---

## 📸 Results

### 🦔 Hedgehog

![Hedgehog 1](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/erizo2.jpeg)
![Hedgehog 2](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/erizo01.png)

---

### 🧸 Doll Head

![Doll Head 1](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/cabeza.jpeg)
![Doll Head 2](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/cabeza1.png)

---

### 🪑 Chair

![Chair 1](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/silla1.jpeg)
![Chair 2](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Proyecto%20Escaner%20Laser%203D/Resultados/silla01.png)

---

## 📦 Technologies Used

- **C++**
- **OpenCV** – image processing and laser line extraction
- **tkViewer** – 3D point cloud visualization

---

## 📚 Purpose

This project demonstrates the application of computer vision and graphics principles to develop a functional 3D scanning system using low-cost components. It serves as an educational prototype to explore real-world 3D reconstruction using structured light.


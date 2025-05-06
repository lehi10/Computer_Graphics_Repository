# 🎯 Final Project – 3D Laser Scanner

**Author**: Lehi Quincho M.  

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
<div style="display: flex; gap: 10px; align-items: center;">
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/erizo2.jpeg" width="300"  />
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/erizo01.png" width="300" />
</div>
---

### 🧸 Doll Head
<div style="display: flex; gap: 10px; align-items: center">
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/cabeza.jpeg" width="300" />
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/cabeza1.png" width="300" />
</div>

---

### 🪑 Chair
<div style="display: flex; gap: 10px; align-items: center">
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/silla1.jpeg" width="300" />
<img src="https://raw.githubusercontent.com/lehi10/Computaci-n-Grafica/master/Proyecto%20Escaner%20Laser%203D/Resultados/silla01.png" width="300" />
</div>

---

---

## 📦 Technologies Used

- **C++**
- **OpenCV** – image processing and laser line extraction
- **tkViewer** – 3D point cloud visualization

---

## 📚 Purpose

This project demonstrates the application of computer vision and graphics principles to develop a functional 3D scanning system using low-cost components. It serves as an educational prototype to explore real-world 3D reconstruction using structured light.


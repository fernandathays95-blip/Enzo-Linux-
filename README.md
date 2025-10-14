# 🐧 Enzo Linux — Sistema Operacional Minimalista do Zero

![Enzo Linux Banner](https://github.com/fernandathays95-blip/Enzo-Linux-/blob/main/Source/banner/enzo-banner.txt)

Enzo Linux é um **sistema operacional híbrido**, escrito em shell script e outros módulos, criado do zero, rodando inicialmente no Termux e com expansão futura para interface gráfica, reconhecimento de toques e módulos avançados.  
Este é um projeto **open-source**, perfeito para quem quer estudar sistemas Linux minimalistas e interativos.

---

## 🚀 Funcionalidades atuais
- Módulos em **SH** para kernel e init.
- Prompt de terminal personalizado (`[EnzoOS]:~$`).
- Sistema modular e expansível.
- Inicialização rápida no Termux (proot).
- Logs detalhados do Kernel GPT.
- Preparado para futura interface gráfica e reconhecimento de toques.

---

## 🌐 Código aberto e site oficial

Clique no botão abaixo para acessar o site oficial do projeto e o repositório completo:

[![Acessar Site do Enzo Linux](https://img.shields.io/badge/Visitar-Site%20do%20Enzo%20Linux-blue?style=for-the-badge&logo=github)](https://github.com/fernandathays95-blip/Enzo-Linux-/tree/main/Source)

> No site você poderá baixar o Enzo Linux, ver documentação detalhada, tutoriais e contribuições do projeto.

---

## 🛠️ Como executar no Termux (versão atual)
```bash
pkg install proot wget tar busybox git -y
git clone https://github.com/SEU_USUARIO/enzo-linux.git
cd enzo-linux
sh start-enzo.sh setup
sh start-enzo.sh

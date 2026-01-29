# add glfw src
git remote add glfw https://github.com/glfw/glfw.git

# add glfw subtree
git subtree add --prefix=external/glfw glfw 1-glfw --squash

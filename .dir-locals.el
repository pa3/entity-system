((nil . ((eval . (progn
                   (require 'projectile)
                   (puthash (projectile-project-root)
                            "cmake . && make && ./EntitySystemTests"
                            projectile-test-cmd-map))))))

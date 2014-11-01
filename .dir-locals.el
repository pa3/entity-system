((nil . ((eval . (progn
                   (require 'projectile)
                   (puthash (projectile-project-root)
                            "mkdir -p bin && cd bin/ && cmake ../ && make && ./EntitySystemTests"
                            projectile-test-cmd-map))))))
